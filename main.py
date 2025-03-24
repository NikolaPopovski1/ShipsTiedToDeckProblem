import ctypes

class Ship:
    def __init__(self, num, pointer):
        self.num = int(num)
        self.pointer = ctypes.c_void_p(pointer)
    

def read_file(input_filename: str, output_filename: str):
    try:
        with open(input_filename, 'r', encoding='utf-8') as infile:
            count = 0
            start = True
            while (start or (N != 0 and M != 0)):
                start = False
                list = []
                line = infile.readline()
                parts = line.split(' ')

                N = int(parts[0])
                M = int(parts[1])
                print(count)
                count += 1
                for incr in range(0, M):
                    line = infile.readline()
                    parts = line.split(' ')
                    i = parts[0]
                    j = parts[1]
                    print(count)
                    count += 1
            
        

        print(f"File '{input_filename}' copied successfully to '{output_filename}'.")
    except FileNotFoundError:
        print(f"Error: '{input_filename}' not found.")
    except Exception as e:
        print(f"An error occurred: {e}")

read_file('testni_primer.txt', 'output.txt')
