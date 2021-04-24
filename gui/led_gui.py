# Build a GUI to send the POST requests to the ESP32 for addressable LED control
# 2021, Graison Mitio
import tkinter as tk
import requests

url = "http://192.168.1.124/post"   # ESP32 Controller URL

def chase():
    txobj = {'body' : '{"LedMode":1}'}
    requests.post(url, data = txobj)

def alternate():
    txobj = {'body' : '{"LedMode":0}'}
    requests.post(url, data = txobj)

def steady():
    txobj = {'body' : '{"LedMode":2, "Color":' + str(w1.get())+ '}'}
    requests.post(url, data = txobj)

window = tk.Tk()
window.title("LED Control")
window.geometry("480x320")

wind_msg = tk.Label(text="LED Strip Control Application")
control_bt_1 = tk.Button(text="Chase Pattern", command=chase)
control_bt_2 = tk.Button(text="Alternating Pattern", command=alternate)
control_bt_3 = tk.Button(text="Steady Pattern", command=steady)

w1 = tk.Scale(window, from_=0, to=16777215, length=400, orient=tk.HORIZONTAL)

w1.pack()
control_bt_1.pack()
control_bt_2.pack()
control_bt_3.pack()
wind_msg.pack()

window.mainloop()