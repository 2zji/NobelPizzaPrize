def font_to_cpp(file_path, cpp_file_name):
    with open(file_path, 'rb') as f:
        binary_data = f.read()

    with open(cpp_file_name, 'w') as cpp_file:
        cpp_file.write(f"unsigned char font_data[] = {{\n")
        for i, byte in enumerate(binary_data):
            cpp_file.write(f"0x{byte:02x}, ")
            if (i + 1) % 12 == 0:
                cpp_file.write("\n")
        cpp_file.write("\n};\n")
        cpp_file.write(f"unsigned int font_data_len = {len(binary_data)};\n")

if __name__ == "__main__":
    font_to_cpp("BagelFatOne-Regular.ttf", "font_data.cpp")
