The program works on linux in x11 environment.originally written for Ubuntu with i3 window manager and i3blocks statusbar installed on it.You will also need to install xrandr. in this configuration everything works fine. with other configurations there should be no problems. in any case I will be glad to get feedback. 

now to the DESCRIPTION:
This utility works in the terminal. It parses the output of the xrandr command 
and, based on the data obtained, gives you a list of available monitors in your system. Then you simply follow the instructions given by the software to connect or disconnect an additional display to your system. The number of displays is limited by the capabilities of your machine.

INSTALL:
1.copy all the files to wherever you want on your computer.The main thing is that all the files should be in the same    directory.
  by default it is recommended to copy to the directory /home/{YOUR_USERNAME}/.config/displayadd
  after that the programm is ready to run.
  If you need to compile and reassemble the program, there is MakeFile, 
  run it with the “make” command in the terminal.

  tip*:
  in this directory (/home/{YOUR_USERNAME}/.config/displayadd) the program always stores its config file under the       name "display.cfg" and it would be convenient    to store everything together.
  if the directory does not exist at the first start the program will create it. config file with default settings       will also be created.

2.If you use for example i3blocks status bar, you can write the following in i3blocks config file in order to get a      shortcut for launching the program from the status bar, when you click on it, the terminal with the program running    in it will be automatically opened.
  To do this, write the following in the i3blocks config:
  [+display]
  command=~/.config/displayadd/launch
  interval=once
  signal=10
  separator_block_width=20


LAUNCH:
To run the program, make sure you have x11 installed and running. and also have xrandr installed.
You can use one of two files to launch a program: both “display” and “launch”. 
so what is the difference:
1."display":
  Simply run “display” from the program files directory by typing ./display in the terminal or if you are using a        graphical file manager, run from there.

2."launch":
  This is essentially a shortcut to run the main program. 
  As described above, you can create a launch shortcut by adding a “launch” file to the status bar config. the above     method is for i3blocks. if you use a different status bar, the description will be different.
  You can also launch the ./launch file simply from the terminal. in this case the program will be launched in a new     terminal endpoint.
  NOTE: "Launch" file will work only if you have all files in the directory “/home/{YOUR_USERNAME}/.config/displayadd”.
  If this is not the case, use the first method. or you can try to change the text of the launch.c file to your liking   and build everything again.


//CONTROLS:
once the program is started,first of all you will be offered a choice of displays available in the system and their status will be indicated. 
simply follow the instructions in the terminal window to run through setup process.
To exit the program without waiting for the configuration to finish, press CTRL+D or go to the last option, where you will be prompted to end the program.
The program is also able to save the last setting as default for use next time.

display status explanations:
-"connected/disconnected" indicates whether the display is physically connected through the port to the computer
-"active/unactive" indicates whether the display is displaying an image or not.


The program is written in C. in June 2025.
any improvements and suggestions are welcome.Enjoy your use)
-"primary" indicates that this is the primary display in the system.
