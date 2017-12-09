import { Component } from '@angular/core';
// import { NavController } from 'ionic-angular';
import { BluetoothSerial } from '@ionic-native/bluetooth-serial';
import { AlertController } from 'ionic-angular';
import { HttpClient } from "@angular/common/http";
import { Geolocation } from '@ionic-native/geolocation';

var studyPlacesApi = 'ws://52.178.92.214:10001';

@Component({
  selector: 'page-home',
  templateUrl: 'home.html'
})
export class HomePage {
  totalDevices: Number;
  pos: Object;
  unpairedDevices: any;
  pairedDevices: any;
  gettingDevices: Boolean;
  connection: any;
  latitude: Number;
  longitude: Number;

  constructor(private bluetoothSerial: BluetoothSerial, private alertCtrl: AlertController, private http: HttpClient, private geo:Geolocation) {
    bluetoothSerial.enable();


    let watch = this.geo.watchPosition();
    watch.subscribe((data) => {
      console.log('data: ', data);
      // data can be a set of coordinates, or an error (if an error occurred).
      this.pos = { latitude: data.coords.latitude, longitude: data.coords.longitude };
      this.latitude = data.coords.latitude;
      this.longitude = data.coords.longitude;
    }, err => {
      console.log('err: ', err);
    });

    // var connection = new WebSocket(studyPlacesApi);
    // this.connection = connection;
    // this.startScanning();

    // connection.onopen = function (res) {
    //   console.log('opened connection to ws://52.178.92.214:10001: ', res);
    //   connection.send('Opened Ping !'); // Send the message 'Ping' to the server
    // };
    // connection.onmessage = function (res) {
    //   console.log('res: ', res);
    //   connection.send('Message  Ping !'); // Send the message 'Ping' to the server
    //   // this.receiveHeatMap(res);
    // };

  }

  postToServer() {
    var body = {"uuid":"testUUID", "longitude": 12313313, "latitude":123211233, "list":[], "total": 25};
    this.http.post('http://52.178.92.214', body)
      .subscribe(result => {
        console.log('result: ', result);
      }, error => { console.error('postToServer error: ', error);});
  }
  receiveHeatMap() {
    console.log('res: ');
    this.connection.send('answer  Ping !'); // Send the message 'Ping' to the server
  }
  startScanning() {
    this.pairedDevices = [];
    this.unpairedDevices = [];
    this.gettingDevices = true;
    this.pos = null;
    var connection = new WebSocket(studyPlacesApi);
    this.connection = connection;
    var self = this;
    // self.connection.onopen = function (res) {
    //   console.log('opened connection to ws://52.178.92.214:10001: ', res);
    //   self.connection.send('Opened Ping !'); // Send the message 'Ping' to the server
    // };
    // self.connection.onmessage = function (res) {
    //   self.receiveHeatMap();
    // };
    this.bluetoothSerial.discoverUnpaired().then((success) => {
        this.unpairedDevices = success;
        this.gettingDevices = false;

        this.totalDevices = this.unpairedDevices.length + this.pairedDevices.length;

        self.connection.onopen = function (res) {
          console.log('opened connection to ws://52.178.92.214:10001: ', res);
          self.connection.send({ "uuid": "BlubUSER", "longitude": self.longitude, "latitude": self.latitude, "list":[], "total": self.totalDevices }); // Send the message 'Ping' to the server
        };
        self.connection.onmessage = function (res) {
          self.receiveHeatMap();
        };
        success.forEach(element => {
          // console.log('elements: ',/* element.name,*/ element);
          //

          // if (this.pos !== null) {
          //   connection.onopen = function (res) {
          //     console.log('opened connection to ws://52.178.92.214:10001: ', res);
          //     connection.send('Opened Ping !'); // Send the message 'Ping' to the server
          //   };
          //   connection.onmessage = function (res) {
          //     this.receiveHeatMap(res);
          //   };
          // }
        });
      },
      (err) => {
        console.error(err);
      });

    this.bluetoothSerial.list().then((success) => {
        console.log('list success: ', success);
        this.pairedDevices = success;
        this.totalDevices = this.unpairedDevices.length + this.pairedDevices.length;
        if (this.pos !== null) {
          // self.connection.onopen = function (res) {
          //   console.log('opened connection to ws://52.178.92.214:10001: ', res);
          //   self.connection.send('Opened Ping !'); // Send the message 'Ping' to the server
          // };
          // self.connection.onmessage = function (res) {
          //   self.receiveHeatMap();
          // };
        }
      },
      (err) => {
        console.error('err: ', err);
      })

    setTimeout(function () {
      this.startScanning();
    }, 30000);

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
