# Software

## Software requirements  

### Software or Libraries to Download

  1. [Arduino IDE](https://www.arduino.cc/en/software)
  2. [Main Code](./Code/)
  3. [Seeed_Arduino_FS](https://github.com/Seeed-Studio/Seeed_Arduino_FS)
  4. [SparkFun_Qwiic_GPIO_Library](https://github.com/sparkfun/SparkFun_Qwiic_GPIO_Library)


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

  1. Visit the **Seeed_Arduino_FS** library github repository page.
  2. Click on **Code > Download Zip** to download **Seeed_Arduino_FS**.
  3. Extract **Seeed_Arduino_FS-master.zip** file
  4. Rename **Seeed_Arduino_FS-master** folder to **Seeed_Arduino_FS** folder under **Seeed_Arduino_FS-master** subdirectory. 
  5. Copy or move **Seeed_Arduino_FS** folder to Arduino installation library subdirectory. As an example: This is found under **C:\Program Files (x86)\Arduino\libraries in windows 10**.
  6. Visit the **SparkFun_Qwiic_GPIO_Library** library github repository page.
  7. Click on **Code > Download Zip** to download **SparkFun_Qwiic_GPIO_Library**.
  8. Extract **SparkFun_Qwiic_GPIO_Library-master.zip** file
  9. Rename **SparkFun_Qwiic_GPIO_Library-master** folder to **SparkFun_Qwiic_GPIO_Library** folder under **SparkFun_Qwiic_GPIO_Library-master** subdirectory. 
  10. Copy or move **SparkFun_Qwiic_GPIO_Library** folder to Arduino installation library subdirectory. As an example: This is found under **C:\Program Files (x86)\Arduino\libraries in windows 10**.
  11. Visit the **Qwiic_Switch_Attempt_Counter.ino** raw source code file under Code directory.
  12. Right click on the source code or any place on this page and select **Save Page As…**
  13. Select the directory you would like to save the software in your computer. 
  14. Change File name from **Qwiic_Switch_Attempt_Counter** to **Qwiic_Switch_Attempt_Counter.ino**
  15. Change **Save as type** to **All Files**.
  16. Click on **Save** button.
  17. Visit the **Free_Fonts.h** raw source code file under Code directory.
  18. Right click on the source code or any place on this page and select **Save Page As…**
  19. Select the directoryyou selected in step 3.
  20. Click on **Save** button.
  21. Open the directory you selected in step 3.
  22. Double left click or open **Qwiic_Switch_Attempt_Counter** file
  23. **Arduino IDE** will ask your permission to create a new sketch folder named **Qwiic_Switch_Attempt_Counter** and move **Qwiic_Switch_Attempt_Counter.ino** under this folder.
  24. Click on the **Ok** button. 
  25. **Arduino IDE** should now open the **Qwiic_Switch_Attempt_Counter.ino** file automatically.
  26. Select the Board under **Tools > Board > Seeed SAMD Boards** as **Seeeduino Wio Terminal**
  27. Select the correct port number under **Tools > Port** which should show COM XX (Seeeduino Wio Terminal) 
  28. Press the **Verify** button to make sure there is no problem with the software and libraries. 
  29. Press **Upload** button 


### microSD Card Setup

Please make sure your microSD is formatted using FAT format before inserting in WIO Terminal.


