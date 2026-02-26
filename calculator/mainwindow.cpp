#include "mainwindow.h"

#include <QDebug>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->l_result->setText("0");
    ui->l_memory->setText("");
    ui->l_formula->setText("");
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::SetText(const QString& text) {
    input_number_ = NormalizeNumber(text);
    active_number_ = input_number_.toDouble();

    ui->l_result->setText(input_number_);

    if (current_operation_ == Operation::NO_OPERATION) {
        ui->l_formula->setText("");
    }
}

void MainWindow::AddText(const QString& suffix) {
    input_number_.push_back(suffix);
    SetText(input_number_);
}

void MainWindow::SetOperation(Operation op) {
    if (current_operation_ == Operation::NO_OPERATION) {
        calculator_.Set(active_number_);
    }

    current_operation_ = op;
    input_number_.clear();

    ui->l_formula->setText(QString::fromStdString("%1 %2")
                               .arg(calculator_.GetNumber())
                               .arg(OpToString(op)));
}

void MainWindow::on_b_zero_clicked() {
    AddText("0");
}

void MainWindow::on_b_one_clicked() {
    AddText("1");
}

void MainWindow::on_b_two_clicked() {
    AddText("2");
}

void MainWindow::on_b_three_clicked() {
    AddText("3");
}

void MainWindow::on_b_four_clicked() {
    AddText("4");
}

void MainWindow::on_b_five_clicked() {
    AddText("5");
}

void MainWindow::on_b_six_clicked() {
    AddText("6");
}

void MainWindow::on_b_seven_clicked() {
    AddText("7");
}

void MainWindow::on_b_eigth_clicked() {
    AddText("8");
}

void MainWindow::on_b_nine_clicked() {
    AddText("9");
}

void MainWindow::on_b_dot_clicked() {
    if (!input_number_.contains('.')) {
        AddText(".");
    }
}

void MainWindow::on_b_plusminus_clicked() {
    if (active_number_ == 0 || std::isnan(active_number_)) {
        return;
    }

    if (input_number_.isEmpty()) {
        input_number_ = QString::number(active_number_);
    }

    if (input_number_.startsWith('-')) {
        SetText(input_number_.mid(1));
    } else {
        SetText(QChar('-') + input_number_);
    }
}

void MainWindow::on_b_backspace_clicked() {
    if (input_number_ == "0") {
        return;
    }

    if (input_number_.size() > 0) {
        input_number_.chop(1);

        SetText(input_number_);
    }
}

void MainWindow::on_b_add_clicked() {
    SetOperation(Operation::ADDITION);
}

void MainWindow::on_b_sub_clicked() {
    SetOperation(Operation::SUBTRACTION);
}

void MainWindow::on_b_mul_clicked() {
    SetOperation(Operation::MULTIPLICATION);
}

void MainWindow::on_b_div_clicked() {
    SetOperation(Operation::DIVISION);
}

void MainWindow::on_b_pow_clicked() {
    SetOperation(Operation::POWER);
}

void MainWindow::on_b_enter_clicked() {
    if (current_operation_ == Operation::NO_OPERATION) {
        return;
    }

    QString formula{"%1 %2 %3 ="};
    QString formula_formatted{formula.arg(calculator_.GetNumber())
                                  .arg(OpToString(current_operation_))
                                  .arg(active_number_)};
    ui->l_formula->setText(formula_formatted);

    switch (current_operation_) {
        case Operation::ADDITION:
            calculator_.Add(active_number_);
            break;
        case Operation::SUBTRACTION:
            calculator_.Sub(active_number_);
            break;
        case Operation::MULTIPLICATION:
            calculator_.Mul(active_number_);
            break;
        case Operation::DIVISION:
            calculator_.Div(active_number_);
            break;
        case Operation::POWER:
            calculator_.Pow(active_number_);
            break;
        case Operation::NO_OPERATION:
            return;
    }

    active_number_ = calculator_.GetNumber();
    ui->l_result->setText(QString::number(active_number_));
    input_number_.clear();
    current_operation_ = Operation::NO_OPERATION;
}

void MainWindow::on_b_clear_clicked() {
    current_operation_ = Operation::NO_OPERATION;
    ui->l_formula->setText("");
    SetText("");
}

void MainWindow::on_b_ms_clicked() {
    mem_ = active_number_;
    ui->l_memory->setText("M");
    is_mem_used_ = true;
}

void MainWindow::on_b_mc_clicked() {
    mem_ = 0.0;
    ui->l_memory->setText("");
    is_mem_used_ = false;
}

void MainWindow::on_b_mr_clicked() {
    if (is_mem_used_) {
        active_number_ = mem_;
        ui->l_result->setText(QString::number(mem_));
        input_number_.clear();
    }
}

QString MainWindow::RemoveTrailingZeroes(const QString& text) const {
    for (qsizetype i = 0; i < text.size(); ++i) {
        if (text[i] != '0') {
            return text.mid(i);
        }
    }
    return "";
}

QString MainWindow::NormalizeNumber(const QString& text) const {
    if (text.isEmpty() || text == "-0" || text == "-") {
        return "0";
    }
    if (text.startsWith('.')) {
        // Рекурсивный вызов.
        return NormalizeNumber("0" + text);
    }
    if (text.startsWith('-')) {
        // Рекурсивный вызов.
        return "-" + NormalizeNumber(text.mid(1));
    }
    if (text.startsWith('0') && !text.startsWith("0.")) {
        return NormalizeNumber(RemoveTrailingZeroes(text));
    }

    return text;
}

QString MainWindow::OpToString(Operation op) const {
    switch (op) {
        case Operation::NO_OPERATION:
            return "";
        case Operation::ADDITION:
            return "+";
        case Operation::DIVISION:
            return "÷";
        case Operation::MULTIPLICATION:
            return "×";
        case Operation::SUBTRACTION:
            return "−";
        case Operation::POWER:
            return "^";
    }
}
