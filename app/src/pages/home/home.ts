import { Component } from '@angular/core';
// import { NavController } from 'ionic-angular';
import { BluetoothSerial } from '@ionic-native/bluetooth-serial';
import { AlertController } from 'ionic-angular';
import { HttpClient } from "@angular/common/http";
// import { webtcp } from "webtcp";

// import { BLE } from '@ionic-native/ble';

@Component({
  selector: 'page-home',
  templateUrl: 'home.html'
})
export class HomePage {
  totalDevices: Number;
  unpairedDevices: any;
  pairedDevices: any;
  gettingDevices: Boolean;

  constructor(private bluetoothSerial: BluetoothSerial, private alertCtrl: AlertController, /*private ble: BLE, */private http: HttpClient) {
    bluetoothSerial.enable();
    var connection = new WebSocket('ws://52.178.92.214:10001', ['TCP']);

    connection.onopen = function () {
      connection.send('Ping=================================================='); // Send the message 'Ping' to the server
    };
  }

  postToServer() {
    var body = {"uuid":"testUUID", "longitude": 12313313, "latitude":123211233, "list":[], "total": 25};
    this.http.post('http://52.178.92.214', body)
      .subscribe(result => {
        console.log('result: ', result);
      }, error => { console.error('postToServer error: ', error);});
  }
  startScanning() {
    this.pairedDevices = [];
    this.unpairedDevices = [];
    this.gettingDevices = true;
    this.bluetoothSerial.discoverUnpaired().then((success) => {
        this.unpairedDevices = success;
        this.gettingDevices = false;
        this.totalDevices = this.unpairedDevices.length + this.pairedDevices.length;
        success.forEach(element => {
          console.log('elements: ',/* element.name,*/ element);
        });
      },
      (err) => {
        console.error(err);
      });

    // this.ble.scan([], 30)
    //   .subscribe(device => {
    //     console.log('device found: ', device);
    //   }, error => { console.error('scan error: ', error);});

    this.bluetoothSerial.list().then((success) => {
        console.log('list success: ', success);
        this.pairedDevices = success;
        this.totalDevices = this.unpairedDevices.length + this.pairedDevices.length;
      },
      (err) => {
        console.error('err: ', err);
      })
  }
  success = (data) => alert(data);
  fail = (error) => alert(error);

  selectDevice(address: any) {

    let alert = this.alertCtrl.create({
      title: 'Connect',
      message: 'Do you want to connect with?',
      buttons: [
        {
          text: 'Cancel',
          role: 'cancel',
          handler: () => {
            console.log('Cancel clicked');
          }
        },
        {
          text: 'Connect',
          handler: () => {
            this.bluetoothSerial.connect(address).subscribe(this.success, this.fail);
          }
        }
      ]
    });
    alert.present();

  }

  disconnect() {
    let alert = this.alertCtrl.create({
      title: 'Disconnect?',
      message: 'Do you want to Disconnect?',
      buttons: [
        {
          text: 'Cancel',
          role: 'cancel',
          handler: () => {
            console.log('Cancel clicked');
          }
        },
        {
          text: 'Disconnect',
          handler: () => {
            this.bluetoothSerial.disconnect();
          }
        }
      ]
    });
    alert.present();
  }
}
