import tkinter as tk
from tkinter import scrolledtext
import subprocess

# Path to your C executable (update this as needed)
EXECUTABLE_PATH = 'D:\\CUFE\\CMP-04\\02\\Compilers\\Project\\Compiler\\base.exe'

def run_lex_yacc(input_text):
    """
    Runs the C-based Lex and Yacc executable with the given input text.
    Returns the output or an error message if something goes wrong.
    """
    try:
        result = subprocess.run(
            [EXECUTABLE_PATH],
            input=input_text.encode('utf-8'),
            capture_output=True,
            check=True
        )
        output = result.stdout.decode('utf-8')
        return output
    except subprocess.CalledProcessError as e:
        return f"Error: {e.stderr.decode('utf-8')}"
    except FileNotFoundError:
        return "Error: Executable not found. Please check the path."
    except Exception as e:
        return f"Unexpected error: {str(e)}"

def process_input():
    """
    Retrieves the input from the editor, processes it using the C executable,
    and displays the output or error in the output text area.
    """
    input_code = input_text.get("1.0", "end-1c")
    output = run_lex_yacc(input_code)
    output_text.config(state="normal")
    output_text.delete("1.0", "end")
    output_text.insert("1.0", output)
    output_text.config(state="disabled")

# Create the main window
root = tk.Tk()
root.title("Lex and Yacc GUI")

# Input label and editor
input_label = tk.Label(root, text="Input Code")
input_label.grid(row=0, column=0, sticky="w", padx=5)
input_text = scrolledtext.ScrolledText(root, width=80, height=20)
input_text.grid(row=1, column=0, padx=5, pady=5, sticky="nsew")

# Process button
process_button = tk.Button(root, text="Process", command=process_input)
process_button.grid(row=2, column=0, pady=5)

# Output label and display area
output_label = tk.Label(root, text="Output")
output_label.grid(row=3, column=0, sticky="w", padx=5)
output_text = scrolledtext.ScrolledText(root, width=80, height=10)
output_text.grid(row=4, column=0, padx=5, pady=5, sticky="nsew")
output_text.config(state="disabled")  # Make output read-only

# Configure grid to make text areas expandable
root.grid_rowconfigure(1, weight=1)
root.grid_rowconfigure(4, weight=1)
root.grid_columnconfigure(0, weight=1)

# Start the application
root.mainloop()