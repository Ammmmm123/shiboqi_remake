import socket
import time
import numpy as np

# ==================== 波形生成函数 ====================

def generate_triangle_wave(num_samples=1024, bit_depth=10):
    """
    生成三角波数据（上升+下降）
    num_samples: 采样点数 (1024)
    bit_depth: 位深度 (10位)
    返回: numpy数组，范围0到2^bit_depth-1
    """
    max_value = 2**bit_depth - 1  # 1023 for 10-bit
    half_samples = num_samples // 2
    up = np.linspace(0, max_value, half_samples, dtype=np.uint16)
    down = np.linspace(max_value, 0, num_samples - half_samples, dtype=np.uint16)
    triangle_wave = np.concatenate([up, down])
    return triangle_wave

def generate_square_wave(num_samples=1024, bit_depth=10, duty_cycle=0.5):
    """
    生成方波数据
    num_samples: 采样点数 (1024)
    bit_depth: 位深度 (10位)
    duty_cycle: 占空比 (0.0-1.0)，默认0.5表示50%高电平
    返回: numpy数组，范围0到2^bit_depth-1
    """
    max_value = 2**bit_depth - 1
    high_samples = int(num_samples * duty_cycle)
    square_wave = np.concatenate([
        np.full(high_samples, max_value, dtype=np.uint16),
        np.zeros(num_samples - high_samples, dtype=np.uint16)
    ])
    return square_wave

def generate_sawtooth_wave(num_samples=1024, bit_depth=10):
    """
    生成锯齿波数据（从0线性上升到最大值，然后突降回0）
    num_samples: 采样点数 (1024)
    bit_depth: 位深度 (10位)
    返回: numpy数组，范围0到2^bit_depth-1
    """
    max_value = 2**bit_depth - 1
    sawtooth_wave = np.linspace(0, max_value, num_samples, dtype=np.uint16)
    return sawtooth_wave

def generate_sine_wave(num_samples=1024, bit_depth=10, cycles=1):
    """
    生成正弦波数据
    num_samples: 采样点数 (1024)
    bit_depth: 位深度 (10位)
    cycles: 周期数，默认1表示一个完整正弦周期
    返回: numpy数组，范围0到2^bit_depth-1
    """
    max_value = 2**bit_depth - 1
    t = np.linspace(0, 2 * np.pi * cycles, num_samples)
    # 正弦波从-1到1，映射到0到max_value
    sine_wave = ((np.sin(t) + 1) / 2 * max_value).astype(np.uint16)
    return sine_wave

def generate_reverse_sawtooth_wave(num_samples=1024, bit_depth=10):
    """
    生成反向锯齿波数据（从最大值线性下降到0，然后突升回最大值）
    num_samples: 采样点数 (1024)
    bit_depth: 位深度 (10位)
    返回: numpy数组，范围0到2^bit_depth-1
    """
    max_value = 2**bit_depth - 1
    reverse_sawtooth = np.linspace(max_value, 0, num_samples, dtype=np.uint16)
    return reverse_sawtooth

# ==================== UDP数据包构造 ====================

def build_udp_packet(voltage_value):
    """
    构造UDP数据包，格式: 55A50700000xxxF0 (8字节)
    其中 xxx 为3个字节的十六进制，表示10位电压值
    
    例如：
    - 十进制 9   -> 55 A5 07 00 00 00 09 F0
    - 十进制 25  -> 55 A5 07 00 00 00 19 F0  (0x19 = 25)
    - 十进制 256 -> 55 A5 07 00 00 01 00 F0  (0x100 = 256)
    - 十进制 1023-> 55 A5 07 00 00 03 FF F0  (0x3FF = 1023)
    
    voltage_value: 10位电压值 (0-1023)
    返回: bytes对象
    """
    if voltage_value < 0 or voltage_value > 1023:
        raise ValueError(f"电压值必须在0-1023范围内，当前值: {voltage_value}")
    
    # 构造数据包: 55 A5 07 00 [byte2] [byte1] [byte0] F0  (8字节)
    # voltage_value 拆分为3个字节（大端序）
    byte0 = voltage_value & 0xFF           # 低8位
    byte1 = (voltage_value >> 8) & 0xFF    # 中8位
    byte2 = (voltage_value >> 16) & 0xFF   # 高8位（对于10位数据永远是0x00）
    
    packet = bytes([
        0x55,       # 固定头部
        0xA5,       # 固定头部
        0x07,       # 固定
        0x00,       # 固定
        byte2,      # 电压值最高字节（对于10位数据总是0x00）
        byte1,      # 电压值中间字节
        byte0,      # 电压值最低字节
        0xF0        # 固定尾部
    ])
    
    return packet

# ==================== UDP发送函数 ====================

def send_waveform_udp(waveform_type='sine', target_ip='192.168.0.2', target_port=5000,
                      num_samples=1024, bit_depth=10, delay_ms=1, **kwargs):
    """
    通过UDP发送波形数据包
    
    waveform_type: 波形类型 ('triangle', 'square', 'sawtooth', 'sine', 'reverse_sawtooth')
    target_ip: 目标IP地址
    target_port: 目标端口
    num_samples: 采样点数，默认1024
    bit_depth: 位深度，默认10
    delay_ms: 每个数据包发送间隔（毫秒），默认1ms
    **kwargs: 额外参数，如 duty_cycle（方波占空比）、cycles（正弦波周期数）
    """
    try:
        # 创建UDP socket
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        print(f"UDP Socket 已创建")
        print(f"目标地址: {target_ip}:{target_port}")
        
        # 根据波形类型生成数据
        waveform_generators = {
            'triangle': generate_triangle_wave,
            'square': generate_square_wave,
            'sawtooth': generate_sawtooth_wave,
            'sine': generate_sine_wave,
            'reverse_sawtooth': generate_reverse_sawtooth_wave
        }
        
        if waveform_type not in waveform_generators:
            raise ValueError(f"不支持的波形类型: {waveform_type}，可选: {list(waveform_generators.keys())}")
        
        # 调用对应的波形生成函数
        generator = waveform_generators[waveform_type]
        import inspect
        sig = inspect.signature(generator)
        valid_kwargs = {k: v for k, v in kwargs.items() if k in sig.parameters}
        data = generator(num_samples=num_samples, bit_depth=bit_depth, **valid_kwargs)
        
        print(f"生成波形: {waveform_type}")
        print(f"数据点数: {len(data)}，电压值范围: {min(data)}-{max(data)}")
        print(f"每包发送间隔: {delay_ms} ms")
        print("=" * 60)
        
        # 循环发送1024个数据包
        packets_sent = 0
        start_time = time.time()
        
        for i, voltage_value in enumerate(data):
            # 构造数据包
            packet = build_udp_packet(int(voltage_value))
            
            # 发送UDP包
            sock.sendto(packet, (target_ip, target_port))
            packets_sent += 1
            
            # 打印进度（每100个包打印一次）
            if (i + 1) % 100 == 0:
                print(f"已发送 {i + 1}/{len(data)} 个数据包 (电压值: {voltage_value})")
            
            # 延迟
            if delay_ms > 0:
                time.sleep(delay_ms / 1000.0)
        
        elapsed_time = time.time() - start_time
        print("=" * 60)
        print(f"发送完成！")
        print(f"总数据包数: {packets_sent}")
        print(f"总耗时: {elapsed_time:.2f} 秒")
        print(f"平均速率: {packets_sent / elapsed_time:.1f} 包/秒")
        
    except socket.error as e:
        print(f"Socket错误: {e}")
    except Exception as e:
        print(f"其他错误: {e}")
        import traceback
        traceback.print_exc()
    finally:
        if 'sock' in locals():
            sock.close()
            print("Socket 已关闭")

# ==================== 测试函数：显示数据包示例 ====================

def test_packet_format():
    """测试并显示数据包格式"""
    print("\n" + "=" * 60)
    print("数据包格式测试 (8字节格式)")
    print("=" * 60)
    
    test_values = [0, 9, 25, 256, 512, 1023]  # 测试不同的值
    
    for val in test_values:
        packet = build_udp_packet(val)
        hex_str = ' '.join([f'{b:02X}' for b in packet])
        hex_compact = ''.join([f'{b:02x}' for b in packet])
        binary_val = f'{val:010b}'  # 10位二进制
        print(f"十进制: {val:4d} (0x{val:03X}, 二进制: {binary_val})")
        print(f"  -> 数据包({len(packet)}字节): {hex_str}")
        print(f"  -> 紧凑格式: {hex_compact}")
    
    print("=" * 60 + "\n")

# ==================== 主程序 ====================

if __name__ == "__main__":
    # ==================== 配置区域（可修改的选项）====================
    
    # UDP目标配置
    TARGET_IP = '192.168.0.2'   # 目标设备IP地址
    TARGET_PORT = 5000           # 目标端口
    
    # 波形配置
    WAVEFORM_TYPE = 'reverse_sawtooth'      # 可选: 'sine', 'square', 'triangle', 'sawtooth', 'reverse_sawtooth'
    NUM_SAMPLES = 1024          # 采样点数（发送的数据包数量）
    BIT_DEPTH = 10              # 位深度（10位ADC）
    
    # 发送配置
    DELAY_MS = 1                # 每个数据包发送间隔（毫秒），0表示无延迟
    
    # 波形特定参数（可选）
    DUTY_CYCLE = 0.5            # 方波占空比（仅对square有效），0.0-1.0
    SINE_CYCLES = 1             # 正弦波周期数（仅对sine有效）
    
    # ===========================================================
    
    print("=" * 60)
    print("UDP波形发送程序")
    print("=" * 60)
    print(f"波形类型: {WAVEFORM_TYPE}")
    print(f"采样点数: {NUM_SAMPLES}")
    print(f"位深度: {BIT_DEPTH} bit")
    print(f"目标地址: {TARGET_IP}:{TARGET_PORT}")
    print("=" * 60)
    
    # 显示数据包格式示例
    test_packet_format()
    
    # 发送波形数据
    send_waveform_udp(
        waveform_type=WAVEFORM_TYPE,
        target_ip=TARGET_IP,
        target_port=TARGET_PORT,
        num_samples=NUM_SAMPLES,
        bit_depth=BIT_DEPTH,
        delay_ms=DELAY_MS,
        duty_cycle=DUTY_CYCLE,  # 方波参数
        cycles=SINE_CYCLES      # 正弦波参数
    )
    
    print("=" * 60)
    print("程序执行完毕")
    print("=" * 60)
