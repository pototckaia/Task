import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.12
import QtQuick.Controls 1.4
import org.qmlplayground.liveimage 1.0

ApplicationWindow {
    id: root
    visible: true
    width: 1200;
    height: 1200


    Button {
       id: btn
       text: "Stop"
       property bool btn_toggel: false

       onClicked: {
           btn.btn_toggel = !btn.btn_toggel;
           if (btn.btn_toggel) {
               btn.text = "Start";
               timer.stop()
           } else {
               btn.text = "Stop";
               timer.start();
           }
       }
    }

    Timer {
        id: timer;
        interval: 500;
        running: true;
        repeat: true
        onTriggered: {
             LiveImageProvider.changeFrame();
        }
    }

    LiveImage  {
      y: btn.height
      width: root.width
      height: root.height - btn.height
      image: LiveImageProvider.img
    }

}
