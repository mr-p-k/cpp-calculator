#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "calculator.h"
#include "enums.h"

#include <QMainWindow>

// Реальзуйте класс главного окна.

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

    // устанавливает вводимое число или результат вычисления в ui->l_result.
    void SetInputText(const std::string& text);

    // устанавливает текст ошибки (подробности об отображении ошибки ниже) в
    // ui->l_result.
    void SetErrorText(const std::string& text);

    // устанавливает текст формулы, отображаемой над вводом числа в
    // ui->l_formula.
    void SetFormulaText(const std::string& text);

    // устанавливает индикатор памяти ui->l_memory.
    void SetMemText(const std::string& text);

    // устанавливает текст экстра-кнопки. Если передано nullopt, то нужно скрыть
    // экстра-кнопку.
    void SetExtraKey(const std::optional<std::string>& key);

    // колбэк-функцию нужно вызывать при нажатии кнопки с цифрами от 0 до 9.
    void SetDigitKeyCallback(std::function<void(int key)> cb);

    // колбэк-функцию нужно вызывать при нажатии кнопки операции (сложение,
    // вычитание, умножение, деление, возведение в степень).
    void SetProcessOperationKeyCallback(std::function<void(Operation key)> cb);

    // колбэк-функцию нужно вызывать при нажатии других кнопок. Они перечислены
    // в типе ControlKey в enums.h
    void SetProcessControlKeyCallback(std::function<void(ControlKey key)> cb);

    // колбэк-функцию нужно вызывать при изменении типа чисел.
    void SetControllerCallback(
        std::function<void(ControllerType controller)> cb);

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

    void on_cmb_controller_currentIndexChanged(int index);

    void on_b_add_clicked();

    void on_b_sub_clicked();

    void on_b_mul_clicked();

    void on_b_div_clicked();

    void on_b_pow_clicked();

    void on_b_enter_clicked();

    void on_b_clear_clicked();

    void on_b_ms_clicked();

    void on_b_mr_clicked();

    void on_b_mc_clicked();

    void on_b_plusminus_clicked();

    void on_b_backspace_clicked();

    void on_tb_extra_clicked();

private:
    Ui::MainWindow* ui;

    std::function<void(int key)> digit_cb_;
    std::function<void(Operation key)> operation_cb_;
    std::function<void(ControlKey key)> control_cb_;
    std::function<void(ControllerType controller)> controller_cb_;
};

#endif  // MAINWINDOW_H
