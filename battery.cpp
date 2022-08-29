#include "battery.h"

Battery::Battery() : battery(100) { }

void Battery::setup(Ui::MainWindow *ui, uint16_t height, uint16_t width) {
  this->ui = ui;
  this->ui->battery->setValue(battery);
  range = battery * efficiency_constant;
  ui->range->display(float(range));

  ui->battery->resize(width * 10 / 100, height * 30 / 100);
  ui->battery->move(width * 20 / 100, height * 50 / 100 - ui->battery->height() / 2);
  ui->range_label->resize(width * 15 / 100, height * 8 / 100);
  ui->range->resize(width * 15 / 100, height * 15 / 100);
  ui->range_label->move(width - width * 90 / 100, height - height * 20 / 100);
  ui->range->move(width - width * 90 / 100 + ui->range_label->width(), height - height * 15 / 100 - ui->range_label->height());
  ui->range->resize(width * 15 / 100, height * 5 / 100);
  ui->range_label->move(ui->range_label->x(), ui->range_label->y() - ui->range->height());
  ui->low_battery_label->resize(width * 10 / 100, width * 10 / 100);
  ui->low_battery_label->move((width - (width * ICON_COUNT) / 10) / 2 +(ui->low_battery_label->width() * LOW_BATTERY_WARNING_ICON), 0);

  ui->battery_line_1->move(width * 20 / 100, height * 50 / 100 - ui->battery->height() / 2 + 50);
  ui->battery_line_2->move(ui->battery_line_1->x(), ui->battery_line_1->y() + height * 10 / 120);
  ui->battery_line_3->move(ui->battery_line_2->x(), ui->battery_line_2->y() + height * 10 / 120);
  ui->battery_line_4->move(ui->battery_line_3->x(), ui->battery_line_3->y() + height * 10 / 120);

  ui->battery_line_1->resize(width * 10 / 100, 1);
  ui->battery_line_2->resize(ui->battery_line_1->width(), ui->battery_line_1->height());
  ui->battery_line_3->resize(ui->battery_line_2->width(), ui->battery_line_2->height());
  ui->battery_line_4->resize(ui->battery_line_3->width(), ui->battery_line_3->height());

  low_battery = QPixmap(":/icons/low-battery.png");
  this->ui->low_battery_label->setText("OFF");

  ui->battery_label->resize(width * 10 / 100, width * 10 / 100);
  ui->battery_label->move((width - (width * ICON_COUNT) / 10) / 2 +(ui->battery_label->width() * BATTERY_WARNING_ICON), 0);

  battery_fault = QPixmap(":/icons/battery.png");
  this->ui->battery_label->setText("OFF");
}

void Battery::increase_battery(uint8_t val) {
  if (battery < 100 && battery > -1) {
    battery += val;
    this->ui->battery->setValue(battery);
    ui->battery->update();
    this->range += efficiency_constant;
    ui->range->display(uint8_t(range));
    check_range();
  }
}

void Battery::decrease_battery(uint8_t val) {
  if (battery < 101 && battery > 1) {
    battery -= val;
    this->ui->battery->setValue(battery);
    ui->battery->update();
    this->range -= efficiency_constant;
    ui->range->display(uint8_t(range));
    check_range();
  }
}

uint8_t Battery::get_battery() { return battery; }

uint8_t Battery::get_range() { return range; }

void Battery::on(warnings warning) {
  if (warning == LOW_BATTERY)
    this->ui->low_battery_label->setPixmap(low_battery);
  else if (warning == BATTERY_FAULT)
    this->ui->battery_label->setPixmap(battery_fault);
}

void Battery::off(warnings warning) {
  if (warning == LOW_BATTERY)
    this->ui->low_battery_label->setText("OFF");
  if (warning == BATTERY_FAULT)
    this->ui->battery_label->setText("OFF");
}

void Battery::check_range() {
  if (get_range() <= 30)
    on(LOW_BATTERY);
  else
    off(LOW_BATTERY);
}
