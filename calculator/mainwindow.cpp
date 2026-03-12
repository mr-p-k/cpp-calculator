#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // т.к. в main.cpp связан контроллер для double
    // то ставим combo box в положение для double
    ui->cmb_controller->setCurrentIndex(
        static_cast<int>(ControllerType::DOUBLE));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::SetInputText(const std::string& text) {
    ui->l_result->setStyleSheet("");
    ui->l_result->setText(QString::fromStdString(text));
}

void MainWindow::SetErrorText(const std::string& text) {
    ui->l_result->setStyleSheet("color: red;");
    ui->l_result->setText(QString::fromStdString(text));
}

void MainWindow::SetFormulaText(const std::string& text) {
    ui->l_formula->setText(QString::fromStdString(text));
}

void MainWindow::SetMemText(const std::string& text) {
    ui->l_memory->setText(QString::fromStdString(text));
}

void MainWindow::SetExtraKey(const std::optional<std::string>& key) {
    if (key) {
        ui->tb_extra->setVisible(true);
        ui->tb_extra->setText(QString::fromStdString(key.value()));
    } else {
        ui->tb_extra->setVisible(false);
    }
}

void MainWindow::SetDigitKeyCallback(std::function<void(int)> cb) {
    digit_cb_ = cb;
}

void MainWindow::SetProcessOperationKeyCallback(
    std::function<void(Operation)> cb) {
    operation_cb_ = cb;
}

void MainWindow::SetProcessControlKeyCallback(
    std::function<void(ControlKey)> cb) {
    control_cb_ = cb;
}

void MainWindow::SetControllerCallback(std::function<void(ControllerType)> cb) {
    controller_cb_ = cb;
}

void MainWindow::on_b_zero_clicked() {
    if (digit_cb_) {
        digit_cb_(0);
    }
}

void MainWindow::on_b_one_clicked() {
    if (digit_cb_) {
        digit_cb_(1);
    }
}

void MainWindow::on_b_two_clicked() {
    if (digit_cb_) {
        digit_cb_(2);
    }
}

void MainWindow::on_b_three_clicked() {
    if (digit_cb_) {
        digit_cb_(3);
    }
}

void MainWindow::on_b_four_clicked() {
    if (digit_cb_) {
        digit_cb_(4);
    }
}

void MainWindow::on_b_five_clicked() {
    if (digit_cb_) {
        digit_cb_(5);
    }
}

void MainWindow::on_b_six_clicked() {
    if (digit_cb_) {
        digit_cb_(6);
    }
}

void MainWindow::on_b_seven_clicked() {
    if (digit_cb_) {
        digit_cb_(7);
    }
}

void MainWindow::on_b_eigth_clicked() {
    if (digit_cb_) {
        digit_cb_(8);
    }
}

void MainWindow::on_b_nine_clicked() {
    if (digit_cb_) {
        digit_cb_(9);
    }
}

void MainWindow::on_cmb_controller_currentIndexChanged(int index) {
    auto contoller_type = static_cast<ControllerType>(index);

    if (controller_cb_) {
        controller_cb_(contoller_type);
    }
}

void MainWindow::on_b_add_clicked() {
    if (operation_cb_) {
        operation_cb_(Operation::ADDITION);
    }
}

void MainWindow::on_b_sub_clicked() {
    if (operation_cb_) {
        operation_cb_(Operation::SUBTRACTION);
    }
}

void MainWindow::on_b_mul_clicked() {
    if (operation_cb_) {
        operation_cb_(Operation::MULTIPLICATION);
    }
}

void MainWindow::on_b_div_clicked() {
    if (operation_cb_) {
        operation_cb_(Operation::DIVISION);
    }
}

void MainWindow::on_b_pow_clicked() {
    if (operation_cb_) {
        operation_cb_(Operation::POWER);
    }
}

void MainWindow::on_b_enter_clicked() {
    if (control_cb_) {
        control_cb_(ControlKey::EQUALS);
    }
}

void MainWindow::on_b_clear_clicked() {
    if (control_cb_) {
        control_cb_(ControlKey::CLEAR);
    }
}

void MainWindow::on_b_ms_clicked() {
    if (control_cb_) {
        control_cb_(ControlKey::MEM_SAVE);
    }
}

void MainWindow::on_b_mr_clicked() {
    if (control_cb_) {
        control_cb_(ControlKey::MEM_LOAD);
    }
}

void MainWindow::on_b_mc_clicked() {
    if (control_cb_) {
        control_cb_(ControlKey::MEM_CLEAR);
    }
}

void MainWindow::on_b_plusminus_clicked() {
    if (control_cb_) {
        control_cb_(ControlKey::PLUS_MINUS);
    }
}

void MainWindow::on_b_backspace_clicked() {
    if (control_cb_) {
        control_cb_(ControlKey::BACKSPACE);
    }
}

void MainWindow::on_tb_extra_clicked() {
    if (control_cb_) {
        control_cb_(ControlKey::EXTRA_KEY);
    }
}
