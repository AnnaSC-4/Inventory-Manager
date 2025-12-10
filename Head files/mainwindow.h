#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// Declaración forward
class databasemanager;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Menús
    void onFileOpen();
    void onFileExit();
    void onHelpAbout();

    // Botones
    void onAgregarClicked();
    void onEliminarClicked();
    void onBuscarTextChanged(const QString &text);

private:
    // Funciones internas
    void configurarTabla();
    void cargarDatosEjemplo();
    void actualizarEstado();

    void agregarProductoATabla(int id, const QString &nombre,
                               const QString &categoria, int cantidad,
                               double precio, const QString &ubicacion);

private:
    Ui::MainWindow *ui;
    databasemanager *m_dbManager;
};

#endif // MAINWINDOW_H
