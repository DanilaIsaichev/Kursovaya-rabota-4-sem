#include "mainwindow.h"
#include "ui_mainwindow.h"

QT_CHARTS_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_vt_clicked()
{
    double F = (convert(ui->F_input->text())).toDouble();
    if (F <= 0) {
        QMessageBox::critical(NULL,QObject::tr("Ошибка"),tr("Сила тяги не может быть меньше или равна нулю!"));
        return;
    }

    double m0 = (convert(ui->m0_input->text())).toDouble();
    if (m0 <= 0) {
        QMessageBox::critical(NULL,QObject::tr("Ошибка"),tr("Масса груза и топлива не может быть меньше или равна нулю!"));
        return;
    }

    double mk = (convert(ui->mk_input->text())).toDouble();
    if (mk <= 0) {
        QMessageBox::critical(NULL,QObject::tr("Ошибка"),tr("Масса топлива не может быть меньше или равна нулю!"));
        return;
    }

    double alpha = (convert(ui->alpha_input->text())).toDouble();
    if (alpha <= 0) {
        QMessageBox::critical(NULL,QObject::tr("Ошибка"),tr("Расход топлива не может быть меньше или равен нулю!"));
        return;
    }

    double ro = 1.29; //Плотность воздуха у поверхности Земли
    const double g = 9.81; //Ускорение свободного падения
    double ht = 0.1; //Шаг по времени
    double c = 0.45; //Коэффициент сопротивления формы (для одноступенчатой ракеты равен в пределах от 0.4 до 0.5)
    double b = 0.00129; //Коэффициент из формулы, отражающей зависимость плотности атмосферы от высоты
    int S = 20; //Площадь поперечного сечения тела
    double tk = (m0 - mk) / alpha; //Время полной выработки топлива
    double v = 0, h = 0, t = 0;

    QChart *chart = new QChart();
    QLineSeries *series = new QLineSeries();
    series->clear();

    while (t <= tk && v <= 1)
    {
        double m = m0 - alpha * t;
        double a = (F - m * g - 0.5 * c * ro * exp(-b * h) * S * v * v) / m;
        v += (a * ht) / 7800;
        h += v * ht;
        series->append((t / tk), v);
        t += ht;
    }

    series->setName("v(t)");

    chart->addSeries(series);
    chart->legend()->hide();
    chart->setTitle("Зависимость скорости от времени");

    QValueAxis *axisX = new QValueAxis;
    axisX->setRange(0, ceil(t / tk)); //Мин. и макс. значения Ox
    axisX->setTitleText("t"); //Подпись оси
    chart->addAxis(axisX, Qt::AlignBottom); //Расположить ось снизу
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(0, 2 * ceil(v)); //Мин. и макс. значения Oy
    axisY->setTitleText("v"); //Подпись оси
    chart->addAxis(axisY, Qt::AlignLeft); //Расположить ось слева
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->Graph->addWidget(chartView, 0, 0);
    }

void MainWindow::on_ht_clicked()
{
    double F = (convert(ui->F_input->text())).toDouble();
    if (F <= 0) {
        QMessageBox::critical(NULL,QObject::tr("Ошибка"),tr("Сила тяги не может быть меньше или равна нулю!"));
        return;
    }

    double m0 = (convert(ui->m0_input->text())).toDouble();
    if (m0 <= 0) {
        QMessageBox::critical(NULL,QObject::tr("Ошибка"),tr("Масса груза и топлива не может быть меньше или равна нулю!"));
        return;
    }

    double mk = (convert(ui->mk_input->text())).toDouble();
    if (mk <= 0) {
        QMessageBox::critical(NULL,QObject::tr("Ошибка"),tr("Масса топлива не может быть меньше или равна нулю!"));
        return;
    }

    double alpha = (convert(ui->alpha_input->text())).toDouble();
    if (alpha <= 0) {
        QMessageBox::critical(NULL,QObject::tr("Ошибка"),tr("Расход топлива не может быть меньше или равен нулю!"));
        return;
    }

    double ro = 1.29; //Плотность воздуха у поверхности Земли
    const double g = 9.81; //Ускорение свободного падения
    double ht = 0.1; //Шаг по времени
    double c = 0.45; //Коэффициент сопротивления формы (для одноступенчатой ракеты равен в пределах от 0.4 до 0.5)
    double b = 0.00129; //Коэффициент из формулы, отражающей зависимость плотности атмосферы от высоты
    int S = 20; //Площадь поперечного сечения тела
    double tk = (m0 - mk) / alpha; //Время полной выработки топлива
    double v = 0, h = 0, t = 0;

    QChart *chart = new QChart();
    QLineSeries *series = new QLineSeries();
    series->clear();

    while (t <= tk && v <= 1)
    {
        double m = m0 - alpha * t;
        double a = (F - m * g - 0.5 * c * ro * exp(-b * h) * S * v * v) / m;
        v += (a * ht) / 7800;
        h += v * ht;
        series->append((t / tk), h);
        t += ht;
    }

    series->setName("h(t)");

    chart->addSeries(series);
    chart->legend()->hide();
    chart->setTitle("Зависимость высоты от времени");

    QValueAxis *axisX = new QValueAxis;
    axisX->setRange(0, ceil(t / tk)); //Мин. и макс. значения Ox
    axisX->setTitleText("t"); //Подпись оси
    chart->addAxis(axisX, Qt::AlignBottom); //Расположить ось снизу
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(0, 2 * ceil(v)); //Мин. и макс. значения Oy
    axisY->setTitleText("h"); //Подпись оси
    chart->addAxis(axisY, Qt::AlignLeft); //Расположить ось слева
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->Graph->addWidget(chartView, 0, 0);
    }
