# glfwdemo1

a example about glfw context object sharing. <br/>
don't work correctly on fedora36. <br/>
work correctly on ubuntu20.04. <br/>

**expect**: 

when you press key 1,2 or 3, the two window will change their triangle's color to red,green or blue at same time.

**problem**:

on fedora36, when you press key,1,2 or 3. only one window will change its triangle's color.  <br/>
I still don't why. I hope someone can help me figure it out.

my enviroment:
```
jack@fedora 
------------ 
OS: Fedora release 36 (Thirty Six) x86_64 
Host: 20FBA05VCD ThinkPad X1 Carbon 4th 
Kernel: 5.19.8-200.fc36.x86_64 
Uptime: 11 days, 14 hours, 17 mins 
Packages: 6001 (rpm), 58 (flatpak), 12 (snap) 
Shell: bash 5.1.16 
Resolution: 1920x1080 
DE: GNOME 42.5 
WM: Mutter 
WM Theme: Adwaita 
Theme: Adwaita [GTK2/3] 
Icons: Adwaita [GTK2/3] 
Terminal: gnome-terminal 
CPU: Intel i5-6200U (4) @ 2.800GHz 
GPU: Intel Skylake GT2 [HD Graphics 520] 
Memory: 6008MiB / 6866MiB 
```
