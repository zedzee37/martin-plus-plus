from tkinter import *

root = Tk()
root.resizable(False, False)

buttons = [False] * 64

def press_button(i, button):
    buttons[i] = not buttons[i]

    if buttons[i]:
        button.configure(text="[x]")
    else:
        button.configure(text="[ ]")


def print_hex():
    num = 0
    for i in range(64):
        num |= int(buttons[i]) << i
    print(f"0x{num:X}")

for y in range(8):
    for x in range(8):
        i = x * 8 + y

        button = Button(root, text="[ ]")
        button.grid(column=y, row=x)
        button.configure(command=lambda i=i, button=button: press_button(i, button))


submit_button = Button(root, text="Print", command=print_hex)
submit_button.grid(column=0, row=9, columnspan=10)

root.mainloop()
