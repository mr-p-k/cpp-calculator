#pragma once

#include "calculator.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

enum class Operation : char {
    NO_OPERATION = 0,
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION,
    POWER,
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void SetText(const QString& text);
    void AddText(const QString& suffix);
    void SetOperation(Operation op);

    QString RemoveTrailingZeroes(const QString& text) const;
    QString NormalizeNumber(const QString& text) const;
    QString OpToString(Operation op) const;

private slots:

    void on_b_zero_clicked();

    void on_b_one_clicked();

    void on_b_two_clicked();

    void on_b_three_clicked();

    void on_b_four_clicked();

    void on_b_five_clicked();

    void on_b_six_clicked();

    void on_b_seven_clicked();

    void on_b_eigth_clicked();

    void on_b_nine_clicked();

    void on_b_dot_clicked();

    void on_b_plusminus_clicked();

    void on_b_backspace_clicked();

    void on_b_pow_clicked();

    void on_b_add_clicked();

    void on_b_sub_clicked();

    void on_b_mul_clicked();

    void on_b_div_clicked();

    void on_b_enter_clicked();

    void on_b_clear_clicked();

    void on_b_ms_clicked();

    void on_b_mc_clicked();

    void on_b_mr_clicked();

private:
    Ui::MainWindow* ui;
    Calculator calculator_{};
    QString input_number_{"0"};
    Number active_number_ = 0.0;
    Operation current_operation_ = Operation::NO_OPERATION;
    double mem_ = 0.0;
    bool is_mem_used_ = false;
};
