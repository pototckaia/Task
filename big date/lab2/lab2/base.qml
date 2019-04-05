import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.12
import QtQuick.Controls 1.4
import org.qmlplayground.dataObject 0.1

ApplicationWindow {
    id: root
    visible: true
    width: 1200;
    height: 1200

    DataObject {
        id: data
    }

    property bool btn_toggel: false

    Button {
       id: btn
       text: "Stop"
       onClicked: {
           btn_toggel = !btn_toggel;
           if (btn_toggel) {
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
          canvas.frame = data.frame
          canvas.requestPaint()
        }
    }

    Canvas {
      id:canvas
      y: btn.height
      width: root.width
      height: root.height - btn.height

      property var frame

      function fillRect(i, j, color) {
          var cellW = Math.round(canvas.width / data.cols)
          var cellH = Math.round(canvas.height / data.rows)
          if (cellH === 0) cellH = 1
          if (cellW === 0) cellW = 1
//          console.log(cellH, cel```lW)

          var ctx = canvas.getContext('2d');
          ctx.fillStyle = color;
          ctx.fillRect(cellW*i, cellH*j, cellW, cellH);
      }

      onPaint: {
          var start = Date.now()
          for (var i = 0; frame && i < frame.length; ++i) {
              var col = Math.trunc(i % data.cols)
              var row = Math.trunc(i / data.rows)
              var rgba = frame[i]
              var color = Qt.rgba(rgba[0], rgba[1], rgba[2], rgba[3])

              canvas.fillRect(col, row, color)
          }
          var end = Date.now()
          console.log(data.frame_count, ((end - start) / data.frame_count) * 100)
      }
    }

}
