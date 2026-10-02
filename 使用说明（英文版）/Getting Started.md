# Getting Started with the Smart Fish

The Smart Fish Kit is an educational product tailored for primary and secondary school students, as well as electronic DIY enthusiasts, to deliver an engaging hands-on project experience.

Below is a step-by-step guide to getting started with the Smart Fish :

***

### Installing the Control Software

First, we need to set up the control software for the Smart Fish Kit.

The Smart Fish Kit is controlled via Bluetooth protocol, so you will need to install a Bluetooth command utility (e.g., BLE Debug Assistant/Bluetooth Debugger) on your computer or mobile phone.

Let’s take the mobile version of Bluetooth Debugger as an example. (The installation package is provided in the repository at [软件/蓝牙调试器_v1.95.apk](../软件/蓝牙调试器_v1.95.apk). Note that this software is a third-party app, and all copyrights belong to its original author.)

Once installed, the app icon will appear on your mobile phone screen.

![image-20260405211624477](../image/鱼上手说明/image-20260405211624477.png)

Of course, any other Bluetooth debugging software is also compatible.

***

### Powering On the Device
The Smart Fish Kit uses a magnetic control switch. To power it on:
1. Prepare a piece of adhesive tape and a magnet.
2. Attach the magnet to the adhesive tape.

<img src="../image/鱼上手说明/45070e72d14eb1a7a028dd371dbbc054.jpg" alt="45070e72d14eb1a7a028dd371dbbc054" style="zoom:20%;" />

3. Stick the tape (with the magnet) to the top of the Smart Fish Kit, as shown below.

<img src="../image/鱼上手说明/b0277b9463b569a0c31fd6f6f5f996a8.jpg" alt="b0277b9463b569a0c31fd6f6f5f996a8" style="zoom:20%;" />

A "click" sound (from the relay activation) confirms that the Smart Fish has been powered on successfully.

***

### Connecting to the Smart Fish Kit
1. Launch the installed Bluetooth software.
2. Scan for Bluetooth devices and connect to the Smart Fish Kit’s Bluetooth signal.

<img src="../image/鱼上手说明/image-20260406093621679.png" alt="image-20260406093621679" style="zoom:30%;" />

> If no devices are detected by the Bluetooth Debugger, check that your phone’s location and Bluetooth services are enabled.

After a successful connection, the software interface will look like this:

<img src="../image/鱼上手说明/image-20260406094656502.png" alt="image-20260406094656502" style="zoom:30%;" />

> A PIN code may be required for the first connection. Enter `0000` or `1234` if prompted.

3. Once connected, enable chat mode and send the command `CMD_a`.

<img src="../image/鱼上手说明/image-20260406095118140.png" alt="image-20260406095118140" style="zoom:30%;" />

A slight wag of the fish’s tail confirms that the Smart Fish Kit is functioning properly.

***

For other professional Bluetooth debugging software, the post-connection interface may look like this:

<img src="../image/鱼上手说明/image-20260406095442593.png" alt="image-20260406095442593" style="zoom:30%;" />

In this case:
1. Select `Unknown Service`.
2. Choose the "Upload Service" option.
3. Send the corresponding commands here.

<img src="../image/鱼上手说明/07ff450e28e619148869c776222f68fe.jpg" alt="07ff450e28e619148869c776222f68fe" style="zoom:30%;" />

### Additional Commands
Once the Smart Fish Kit is operational, you can try sending additional commands. Basic commands are listed below:

| Command | Function Description             |
| ------- | -------------------------------- |
| `CMD_S` | Return tail to center position   |
| `CMD_R` | Continuous tail wag to the right |
| `CMD_L` | Continuous tail wag to the left  |
| `CMD_a` | ±15° wag (low speed)             |
| `CMD_A` | ±15° wag (high speed)            |
| `CMD_b` | ±30° wag (low speed)             |
| `CMD_B` | ±30° wag (high speed)            |
| `CMD_c` | ±45° wag (low speed)             |
| `CMD_C` | ±45° wag (high speed)            |

For more custom advanced commands, refer to the document in the folder: [Smart Fish Control Command Guide](Smart Fish Control Command Guide.PDF)

***

### Customizing Control Buttons
Repeatedly editing command text can be cumbersome during operation. To simplify this:

1. Open the following interface in the Bluetooth Debugger:

<img src="../image/鱼上手说明/image-20260406100406459.png" alt="image-20260406100406459" style="zoom:30%;" />

2. Enable edit mode.
3. Select a button to customize the command it sends.

<img src="../image/鱼上手说明/image-20260406100615680.png" alt="image-20260406100615680" style="zoom:30%;" />

4. Edit the button name and the data sent when the button is pressed or released (only one of the "press" or "release" event data fields needs to be configured).

> IMPORTANT: Do NOT enable HEX transmission!!!

<img src="../image/鱼上手说明/image-20260406101116347.png" alt="image-20260406101116347" style="zoom:30%;" />

***

### Notes for Underwater Use
If the Smart Fish Kit is to be used underwater, additional waterproofing measures are mandatory, including but not limited to:
- Add and adjust counterweights to ensure the kit floats semi-submerged and balanced on the water surface.
- Encase internal electronic components in a waterproof sealable bag for protection.
- Wrap Teflon tape around internal knob connections to enhance water resistance.
- Apply waterproof tape to external joints of the kit to ensure full system waterproofing.