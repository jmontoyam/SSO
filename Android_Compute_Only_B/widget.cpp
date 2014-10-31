#include "widget.h"
#include "ui_widget.h"
#include"simulation_compute_only_B.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    ui->mean_edit->setText("");
    ui->std_edit->setText("");

    int K = ui->K_edit->text().toInt() ;
    int T = ui->T_edit->text().toInt();
    int N = ui->N_edit->text().toInt();

    double mean_elapsed_time = 0;
    double  std_elapsed_time = 0;



#ifdef Q_OS_ANDROID

    //use stringstream to convert int to string because
    //ndk des not support c++11 function std::to_string yet
     std::stringstream converter_N;
     std::stringstream converte_K;

     converter_N << N;
     converte_K << K;

    std::string path_to_data =
     std::string("/sdcard/Measuring_Time/Simulation_Compute_Only_B/Varying_K") +
     std::string("/N") + converter_N.str() +
     std::string("/K") +
     converte_K.str() + "/Data";

    simulation_compute_only_B( N, K, T, path_to_data,
                                   mean_elapsed_time, std_elapsed_time, "/sdcard/test_SSO_computing_B.txt");

#else
    std::string path_to_data =
     std::string("../Measuring_Time/Simulation_Compute_Only_B/Varying_K") +
     std::string("/N") + std::to_string(N) +
     std::string("/K") +
     std::to_string(K) + "/Data";

    simulation_compute_only_B( N, K, T, path_to_data,
                                   mean_elapsed_time, std_elapsed_time, "");

#endif

    ui->mean_edit->setText( QString::number(mean_elapsed_time) );
    ui->std_edit->setText( QString::number(std_elapsed_time) );

}
