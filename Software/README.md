# Software

## Software requirements  

### Software or Libraries to Download

  1. [Arduino IDE](https://www.arduino.cc/en/software)
  2. [Main Code](./Code/)


## Software Setup Process

### Debuggers and Compilers Setup Process

  1. Download the [Arduino IDE](https://www.arduino.cc/en/software) executable installation file suitable for your OS.
  2. Double click on the executable file to Install the **Arduino IDE**.
  3. Open and start the **Arduino IDE**.
  4. Go to **File > Preferences**.
  5. Add following link as a new line under **Additional Board Manager URLs** : https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json
  6. Restart the **Arduino IDE**
  7. Open the **Boards Manager** option from the **Tools > Board** menu and install **Seeed SAMD Boards by Seeed Studio**
  8. Wait until the IDE finishes installing the cross-compiling toolchain and tools associated with Board Support Package. This may take few minutes.
  9. That’s it! The installation of **Arduino IDE** and the Board Support Packages is completed.

### Main Code Setup Process

  1. Visit the **Qwiic_Switch_Attempt_Counter.ino** raw source code file under Code directory.
  2. Right click on the source code or any place on this page and select **Save Page As…**
  3. Select the directory you would like to save the software in your computer. 
  4. Change File name from **Qwiic_Switch_Attempt_Counter** to **Qwiic_Switch_Attempt_Counter.ino**
  5. Change **Save as type** to **All Files**.
  6. Click on **Save** button.
  7. Visit the **Free_Fonts.h** raw source code file under Code directory.
  8. Right click on the source code or any place on this page and select **Save Page As…**
  9. Select the directoryyou selected in step 3.
  10. Click on **Save** button.
  11. Open the directory you selected in step 3.
  12. Double left click or open **Qwiic_Switch_Attempt_Counter** file
  13. **Arduino IDE** will ask your permission to create a new sketch folder named **Qwiic_Switch_Attempt_Counter** and move **Qwiic_Switch_Attempt_Counter.ino** under this folder.
  14. Click on the **Ok** button. 
  15. **Arduino IDE** should now open the **Qwiic_Switch_Attempt_Counter.ino** file automatically.
  16. Select the Board under **Tools > Board > Seeed SAMD Boards** as **Seeeduino Wio Terminal**
  17. Select the correct port number under **Tools > Port** which should show COM XX (Seeeduino Wio Terminal) 
  18. Press the **Verify** button to make sure there is no problem with the software and libraries. 
  19. Press **Upload** button 


