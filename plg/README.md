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

