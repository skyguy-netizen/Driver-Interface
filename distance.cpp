#include "distance.h"
#include "scaler.h"

Distance::Distance() : distance(0)
{

}

void Distance::setup(Ui::MainWindow* ui) {
    this->ui = ui;
    ui->distance->display(distance);
    int distanceSize = screenWidth*.05;

    ui->distanceLabel->resize(distanceSize, distanceSize);
    ui->distanceLabel->move(screenWidth/5, screenHeight*.45);
    ui->distance->resize(screenWidth/6,distanceSize*1.2);
    ui->distance->move(screenWidth/5, screenHeight*.45);
}

void Distance::decrease_distance(int value) {
    if(distance - value > -1){
        this->distance -= value;
            ui->distance->display(distance);
    }

}

void Distance::increase_distance(int value) {
this->distance += value;
    ui->distance->display(distance);
}
