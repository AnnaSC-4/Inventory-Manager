#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "databasemanager.h"

#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QKeySequence>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QInputDialog>
#include <QFont>
#include <QDebug>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_dbManager(nullptr)  // Inicializar como nullptr
{
    ui->setupUi(this);

    // Intentar conectar a la base de datos (SIMULADO)
    m_dbManager = new databasemanager(this);
    if (m_dbManager->conectar()) {
        qDebug() << "Base de datos conectada";
    } else {
        qDebug() << "Modo sin base de datos";
    }

    // ===== CONEXIÓN DE BOTONES =====
    connect(ui->Agregar, &QPushButton::clicked,
            this, &MainWindow::onAgregarClicked);

    connect(ui->Eliminar, &QPushButton::clicked,
            this, &MainWindow::onEliminarClicked);

    connect(ui->lineEditBucar, &QLineEdit::textChanged,
            this, &MainWindow::onBuscarTextChanged);

    // ===== CONFIGURAR TABLA =====
    configurarTabla();

    // ===== CARGAR DATOS DE EJEMPLO =====
    cargarDatosEjemplo();

    // ===== ACTUALIZAR ESTADO =====
    actualizarEstado();

    // ===== CREAR MENÚ ARCHIVO =====
    QMenu *fileMenu = menuBar()->addMenu(tr("&Archivo"));

    QAction *openAction = fileMenu->addAction(tr("&Abrir"));
    openAction->setShortcut(QKeySequence::Open);
    connect(openAction, &QAction::triggered, this, &MainWindow::onFileOpen);

    fileMenu->addSeparator();

    QAction *exitAction = fileMenu->addAction(tr("&Salir"));
    exitAction->setShortcut(QKeySequence::Quit);
    connect(exitAction, &QAction::triggered, this, &MainWindow::onFileExit);

    // ===== CREAR MENÚ AYUDA =====
    QMenu *helpMenu = menuBar()->addMenu(tr("&Ayuda"));

    QAction *aboutAction = helpMenu->addAction(tr("&Acerca de"));
    connect(aboutAction, &QAction::triggered, this, &MainWindow::onHelpAbout);
}

MainWindow::~MainWindow()
{
    delete m_dbManager;
    delete ui;
}

// ===== FUNCIONES DE MENÚ =====

void MainWindow::onFileOpen()
{
    QMessageBox::information(this, tr("Abrir"),
        tr("Abrir archivo seleccionado."));
}

void MainWindow::onFileExit()
{
    close();
}

void MainWindow::onHelpAbout()
{
    QMessageBox::about(this, tr("Acerca de InventoryManager"),
        tr("Inventory Manager v1.0\nGestor de inventario."));
}

// ===== FUNCIÓN AUXILIAR PRINCIPAL =====

void MainWindow::agregarProductoATabla(int id, const QString &nombre,
                                       const QString &categoria, int cantidad,
                                       double precio, const QString &ubicacion)
{
    QTableWidget* tabla = findChild<QTableWidget*>();
    if (!tabla) {
        qDebug() << "Error: No se encontró la tabla";
        return;
    }

    int row = tabla->rowCount();
    tabla->insertRow(row);

    // Columna 0: ID
    QTableWidgetItem *itemId = new QTableWidgetItem(QString::number(id));
    itemId->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    tabla->setItem(row, 0, itemId);

    // Columna 1: Nombre
    tabla->setItem(row, 1, new QTableWidgetItem(nombre));

    // Columna 2: Categoría
    tabla->setItem(row, 2, new QTableWidgetItem(categoria));

    // Columna 3: Cantidad
    QTableWidgetItem *itemCantidad = new QTableWidgetItem(QString::number(cantidad));
    itemCantidad->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    if (cantidad < 5) {
        itemCantidad->setForeground(Qt::red);
        itemCantidad->setFont(QFont("", -1, QFont::Bold));
    }
    tabla->setItem(row, 3, itemCantidad);

    // Columna 4: Precio
    QString precioFormateado = QString("$%L1").arg(precio, 0, 'f', 2);
    QTableWidgetItem *itemPrecio = new QTableWidgetItem(precioFormateado);
    itemPrecio->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    tabla->setItem(row, 4, itemPrecio);

    // Columna 5: Ubicación
    tabla->setItem(row, 5, new QTableWidgetItem(ubicacion));
}

// ===== CONFIGURACIÓN INICIAL =====

void MainWindow::configurarTabla()
{
    QTableWidget* tabla = findChild<QTableWidget*>();
    if (!tabla) return;

    tabla->setAlternatingRowColors(true);
    tabla->setSelectionBehavior(QAbstractItemView::SelectRows);
    tabla->setSelectionMode(QAbstractItemView::SingleSelection);
    tabla->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tabla->setSortingEnabled(true);
    tabla->horizontalHeader()->setStretchLastSection(true);
}

void MainWindow::cargarDatosEjemplo()
{
    QTableWidget* tabla = findChild<QTableWidget*>();
    if (!tabla) return;

    tabla->setRowCount(0);

    // Datos de ejemplo (simulados)
    agregarProductoATabla(101, "Laptop Dell XPS 13", "Electrónica", 8, 1299.99, "Almacén A");
    agregarProductoATabla(102, "Mouse Logitech MX", "Accesorios", 25, 79.99, "Almacén B");
    agregarProductoATabla(103, "Monitor 24\" Samsung", "Electrónica", 3, 199.99, "Almacén A");
    agregarProductoATabla(104, "Teclado Mecánico", "Accesorios", 15, 89.99, "Almacén B");
    agregarProductoATabla(105, "Router WiFi 6", "Redes", 10, 149.99, "Almacén C");

    actualizarEstado();
}

// ===== FUNCIONES DE BOTONES =====

void MainWindow::onAgregarClicked()
{
    bool ok;
    QString nombre = QInputDialog::getText(this, "Agregar Producto",
                                          "Nombre del producto:",
                                          QLineEdit::Normal, "", &ok);

    if (ok && !nombre.isEmpty()) {
        QTableWidget* tabla = findChild<QTableWidget*>();
        int nuevoId = 100 + (tabla ? tabla->rowCount() : 0) + 1;

        agregarProductoATabla(nuevoId, nombre, "General", 1, 0.0, "Sin ubicación");
        actualizarEstado();
        QMessageBox::information(this, "Éxito", "Producto agregado (Simulado)");
    }
}

void MainWindow::onEliminarClicked()
{
    QTableWidget* tabla = findChild<QTableWidget*>();
    if (!tabla) return;

    int row = tabla->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Advertencia",
                           "Selecciona un producto de la tabla primero.");
        return;
    }

    QString nombre = tabla->item(row, 1)->text();

    QMessageBox::StandardButton respuesta;
    respuesta = QMessageBox::question(this, "Confirmar",
        QString("¿Eliminar el producto '%1'?").arg(nombre),
        QMessageBox::Yes | QMessageBox::No);

    if (respuesta == QMessageBox::Yes) {
        // La eliminación es solo en la GUI en esta versión simulada.
        tabla->removeRow(row);
        actualizarEstado();
    }
}

// ===== BÚSQUEDA =====

void MainWindow::onBuscarTextChanged(const QString &text)
{
    QTableWidget* tabla = findChild<QTableWidget*>();
    if (!tabla) return;

    QString busqueda = text.toLower();

    for (int row = 0; row < tabla->rowCount(); ++row) {
        bool coincide = false;

        for (int col = 0; col < tabla->columnCount(); ++col) {
            QTableWidgetItem* item = tabla->item(row, col);
            if (item && item->text().toLower().contains(busqueda)) {
                coincide = true;
                break;
            }
        }

        tabla->setRowHidden(row, !coincide && !busqueda.isEmpty());
    }
}

// ===== ACTUALIZAR ESTADO =====

void MainWindow::actualizarEstado()
{
    QTableWidget* tabla = findChild<QTableWidget*>();
    QLabel* labelEstado = findChild<QLabel*>();

    if (!tabla || !labelEstado) return;

    int total = tabla->rowCount();
    int stockBajo = 0;

    for (int row = 0; row < total; ++row) {
        QTableWidgetItem* item = tabla->item(row, 3);
        if (item && item->text().toInt() < 5) {
            stockBajo++;
        }
    }

    QString estado = QString("Total: %1 productos | Stock bajo: %2")
                        .arg(total).arg(stockBajo);
    labelEstado->setText(estado);
}
