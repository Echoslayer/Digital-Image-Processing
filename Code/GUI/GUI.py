import tkinter as tk
from tkinter import filedialog
from PIL import Image, ImageTk
from pathlib import Path
import subprocess
import sys

sys.path.append('../Notebooks/')
from mymodules.image_manager import ImageManager

class ImageApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Image Viewer")
        self.root.geometry("1000x700")
        self.root.configure(bg='gray')  # 設定背景顏色以便更好地突出圖片

        # Create main frame to hold all sections
        self.main_frame = tk.Frame(self.root)
        self.main_frame.pack(fill="both", expand=True)

        # Create frames for different sections
        self.image_frame = tk.Frame(self.main_frame, width=800, height=600, bg='gray')
        self.image_frame.grid(row=0, column=0, padx=5, pady=5)
        self.image_frame.grid_propagate(False)

        self.button_frame = tk.Frame(self.main_frame, width=200, height=600, bg='lightgray')
        self.button_frame.grid(row=0, column=1, padx=5, pady=5, sticky="n")
        self.button_frame.grid_propagate(False)

        self.text_frame = tk.Frame(self.main_frame, width=1000, height=100, bg='white')
        self.text_frame.grid(row=1, column=0, columnspan=2, padx=5, pady=5, sticky="ew")
        self.text_frame.grid_propagate(False)

        # Configure grid weights
        self.main_frame.grid_rowconfigure(0, weight=4)
        self.main_frame.grid_rowconfigure(1, weight=1)
        self.main_frame.grid_columnconfigure(0, weight=4)
        self.main_frame.grid_columnconfigure(1, weight=1)

        # Button to load image
        self.load_button = tk.Button(self.button_frame, text="Load Image", command=self.load_image)
        self.load_button.pack(pady=10)

        # Button to show terminal output
        self.show_terminal_button = tk.Button(self.button_frame, text="Show Terminal Output", command=self.show_terminal_output)
        self.show_terminal_button.pack(pady=10)

        # Label to display image
        self.image_label = tk.Label(self.image_frame, bg='gray')  # 設置背景以便更好地與窗口融合
        self.image_label.place(relx=0.5, rely=0.5, anchor="center")

        # Text widget to display text
        self.text_widget = tk.Text(self.text_frame, wrap="word", height=6)
        self.text_widget.pack(fill="both", expand=True, padx=5, pady=5)

    def load_image(self):
        # Open file dialog to select an image file
        file_path = filedialog.askopenfilename()
        if file_path:
            origin_image_path = Path(file_path)

            # Use ImageManager to manage the image
            origin_im = ImageManager(origin_image_path.as_posix())
            origin_im.choose_rgb('b')

            # Convert the image to a format that tkinter can use
            image = Image.fromarray(origin_im.image)

            # 縮放圖片以適應窗口大小
            self.resize_image(image)

    def resize_image(self, image):
        # 取得視窗的大小
        frame_width = 800
        frame_height = 600

        # 計算圖片縮放比例，保持圖片原始比例
        img_width, img_height = image.size
        scale = min(frame_width / img_width, frame_height / img_height)

        # 縮放圖片以適應視窗
        new_width = int(img_width * scale)
        new_height = int(img_height * scale)
        resized_image = image.resize((new_width, new_height), Image.LANCZOS)

        # 將縮放後的圖片轉換為 tkinter 可用的格式
        image_tk = ImageTk.PhotoImage(resized_image)

        # 顯示圖片於 label 中間
        self.image_label.config(image=image_tk)
        self.image_label.image = image_tk

    def show_terminal_output(self):
        # 執行指令並顯示在文字區域
        command = "echo Terminal Output Example"
        result = subprocess.run(command, shell=True, capture_output=True, text=True)
        self.text_widget.delete("1.0", tk.END)
        self.text_widget.insert(tk.END, result.stdout)

if __name__ == "__main__":
    root = tk.Tk()
    app = ImageApp(root)
    root.mainloop()