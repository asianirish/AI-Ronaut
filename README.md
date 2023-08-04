![Logo](img/AIronautApplicationSymbolicIconWhiteBlueYellow1.png) 
# AI-Ronaut 


## Introduction

This is an **unofficial** client QT based application with a graphical user interface (GUI) for interacting with the OpenAI API

To access the Openal API, this application uses our OAIC libraries. Currently, OAIC is part of the AI-Ronaut project and is distributed under the same license. In the future, we plan to create a separate project for OAIC and use OAIC as a static library subproject.

### Prerequisites

- Qt development environment

### Installation

1. Clone the repository
2. Open the project in the Qt development environment
3. Build the project

## Usage

After successfully building the project, you need to set an environment variable called **OPENAI_API_KEY** with the value of the key obtained from the OpenAI API.

## Efficient Client-Side Computations

A distinctive advantage of our C++ client lies in its ability to handle intensive computations on the client side, independent of the OpenAI API. This allows for significant performance benefits, particularly for applications that require high computational power and efficiency. As we move forward, we plan to further optimize and enhance this feature, to provide an even more powerful tool for your AI development needs.

## Plugins

### Overview

Our application now supports third-party plugins in the form of dynamic libraries, both for Linux and Windows users. These plugins allow for enhanced flexibility and can be used to extend the functionality of the program. 

### Creating a Plugin

To create a plugin, developers need to create a class that inherits from the `IRootObject` interface class and override its virtual functions. 

Here is an example:

```cpp
class RootObject : public QObject, public IRootObject
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.asianirish.IRootObject" FILE "ExamplePlugin.json")
    Q_INTERFACES(IRootObject)
public:
    explicit RootObject(QObject *parent = nullptr);

    void doIt() const override;

    PageWidget *createPageWidget(QWidget *parent) const override;

    plg::Info pluginInfo() const override;

signals:

};
```

### Registering and Using a Plugin

To use a plugin, you first need to register it with the application. This can be done using the `Register Plugin` command, which copies the plugin file and records information about the plugin (title, description, author, plugin version, and plugin file hash code) in a database. 

After registering the plugin, the application will automatically verify its integrity at startup by checking its hash code. If the hash code in the database matches the hash code of the file, the application will open a tab with the plugin's widget.

**Note:** If you encounter any issues or have any questions, please feel free to raise an issue on our GitHub repository. We value your feedback and contributions.

Make sure that your plugins are compatible with the application's current version to avoid any potential issues.

## Licenses

This project is distributed under two licenses: the [CC BY-NC-SA](https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode.txt) License and a commercial license. This means:

1. You are free to use, modify, and distribute this project under the terms of the [CC BY-NC-SA](https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode.txt) License.
2. If you plan to use this project for commercial purposes, you need to obtain a commercial license. Please contact us at asianirish@gmail.com for more information on the commercial license.

We aim to maintain the openness and accessibility of this project by providing the permissive [CC BY-NC-SA](https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode.txt) License. However, we also understand that some organizations may be interested in commercial usage. We offer the option of a commercial license to provide additional support and development for the project.

Additionally, we offer paid customization of the software, including the development of new features based on your specific needs. For inquiries and more details, please reach out to us at asianirish@gmail.com.

## Donate

If you appreciate these services and would like to show your gratitude, you can support the project by donating through **PayPal** or by sending a direct bank transfer.

**PayPal**: [Donate now](https://www.paypal.com/donate/?hosted_button_id=3YRL2X3VBVFLQ)

**EUR**: \
IBAN: PL 15 1050 1793 1000 0097 4489 2788 \
BIC SWIFT: INGBPLPW \
Authorised persons: RISHAT BEKMUKHAMEDOV

**USD**: \
IBAN: PL 47 1050 1793 1000 0097 5843 2927 \
BIC SWIFT: INGBPLPW \
Authorised persons: RISHAT BEKMUKHAMEDOV

**PLN**:  \
IBAN: PL 36 1050 1793 1000 0091 3841 5139 \
BIC SWIFT: INGBPLPW \
Authorised persons: RISHAT BEKMUKHAMEDOV


**ETH**: 0xC318401Feb332A2d906e19Bc2E20A0d3661c5250 \
**BTC**: bc1ql9f70c5ujukus24nzfrvpy29lz67urc80m7fp4 \
**XX**: 6WaZ4Mt7gVj5MxQ9gZEHDpyJ5Yp11SUWhHt77T3YuF8vbZyy \
**QRL**: Q0105006c4cf1793f416e1858d607bcfb28b8b161b46d08da94c4d1eb3d151d3ddd5a8a13909d87


## Supporters

This project is made possible thanks to the generous support of individuals and organizations. If you find this project useful and wish to show your support, you can do so by making a donation.

The following individuals have made significant contributions:

    [- Your Name or Nickname Could Be Here!]
    [- Your Name or Nickname Could Be Here!]
    [- Your Name or Nickname Could Be Here!]

If you'd like to support this project, please consider donating.
