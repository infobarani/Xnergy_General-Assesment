def generate_output_file(filename, values):
    """
    Generate output text file with repeated integers.

    Args:
    filename (str): Name of the output file.
    values (tuple): Tuple containing two integers and a repeat count.
    """
    try:
        with open(filename, 'w') as file:
                for val in values:
                    num1, num2, repeat_count = val
                    for _ in range(int(repeat_count/10)):
                        file.write(f"{num1} {num2}\n")        
        print(f"Output file '{filename}' generated successfully.")
    
    except Exception as e:
        print(f"Error generating output file: {str(e)}")


# Example usage
filename = "test/inputs.txt"
active_high_values =   [(0, 0, 100),
                        (1, 0, 60),
                        (0, 0, 300),
                        (1, 0, 60),
                        (0, 0, 400),
                        (1, 0, 20),
                        (0, 0, 600),
                        (0, 1, 60), 
                        (0, 0, 3000),
                        (0, 1, 80),
                        (0, 0, 6000),
                        (0, 1, 70),
                        (0, 0, 3000),
                        (1, 1, 100),
                        (0, 0, 100),]

active_low_values =   [ (1, 0, 100),
                        (0, 0, 60),
                        (1, 0, 300),
                        (0, 0, 60),
                        (1, 0, 400),
                        (0, 0, 20),
                        (1, 0, 600),
                        (1, 1, 60), 
                        (1, 0, 3000),
                        (1, 1, 80),
                        (1, 0, 6000),
                        (1, 1, 70),
                        (1, 0, 3000),
                        (0, 1, 100),
                        (1, 0, 100),] 
generate_output_file(filename, active_high_values)