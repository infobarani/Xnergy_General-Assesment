import re
import matplotlib.pyplot as plt
import pandas as pd

def parse_log(log_string):
    
    # Regular expression pattern to match log lines
    pattern = r"T:\s*(\d+)\s+I:(.)(.)\s+G:(\w+)\s+R:(\w+)"
    
    # Initialize dictionary to store extracted values
    log_data = {}
    
    # Split log into lines
    log_lines = log_string.splitlines()
    parsed_log = []
    # Iterate over log lines
    for line in log_lines:
        # Match log line using regular expression pattern
        match = re.match(pattern, line)
        
        if match:
            # Extract values from match
            time = int(match.group(1))
            input0 = 0 if match.group(2) == '_' else 1
            input1 = 0 if match.group(3) == '_' else 1
            green_led = 1 if match.group(4) == 'O' else 0
            red_led = 1 if match.group(5) == 'O' else 0
            
            # Store extracted values in dictionary
            log_data = {
                "time": time,
                "pb_1": input0,
                "pb_2": input1,
                "green_led": green_led,
                "red_led": red_led
            }
            parsed_log.append(log_data)
    return parsed_log


def read_log_file(file_path):
    try:
        with open(file_path, 'r') as file:
            log_string = file.read()
        return log_string
    except FileNotFoundError:
        print(f"Error: File '{file_path}' not found.")
        return None

def main():
    file_path = "outputs.txt"
    log_string = read_log_file(file_path)
    
    if log_string:
        log_data = parse_log(log_string)

         # Convert log data to Pandas DataFrame
        df = pd.DataFrame(log_data)
        print(df)

        # Plot DataFrame
        fig, axs = plt.subplots(4, 1, figsize=(10, 12))
        axs[0].plot(df['time'], df['pb_1'], label='pb_1', marker='o')
        axs[0].set_title('pb_1')
        axs[0].set_ylabel('State')

        axs[1].plot(df['time'], df['green_led'], label='green_led', marker='o', color = 'g')
        axs[1].set_title('green_led')
        axs[1].set_ylabel('State')
        
        axs[2].plot(df['time'], df['pb_2'], label='pb_2', marker='o')
        axs[2].set_title('pb_2')
        axs[2].set_ylabel('State')

        axs[3].plot(df['time'], df['red_led'], label='red_led', marker='o', color = 'r')
        axs[3].set_title('red_led')
        axs[3].set_ylabel('State')
        plt.show()

if __name__ == "__main__":
    main()