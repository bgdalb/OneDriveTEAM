#include "recyclebinview.h"
#include "ui_recyclebinview.h"
#include "../../Request/Request/Request.h"
#include <qpainter.h>
#include "QMouseEvent"
#include "math.h"
#include "Utilites.h";

RecycleBinView::RecycleBinView(QWidget* parent) :
	QWidget(parent),
	ui(new Ui::RecycleBinView)
{
	ui->setupUi(this);
	m_eot.push_back('2');
	m_eot.push_back(EOF);
}

void RecycleBinView::setConnection(ServerConnector& con)
{
	this->m_con = std::make_unique<ServerConnector>(con);
}

void RecycleBinView::setUsername(const QString& username)
{
	this->m_username = username;
}

void RecycleBinView::paintEvent(QPaintEvent* event)
{
	QPainter p(this);
	const float x = 10.f;
	int y = 50.f;
	for (int i = 0; i < m_files.size(); i++)
	{
		QPoint textposition;
		textposition.setX(x);
		textposition.setY(y);
		if (m_colors[i] == 0)
			p.setPen(Qt::black);
		else
			p.setPen(Qt::red);
		QString filename = QString::fromStdString(m_files[i].toStdString().substr(m_files[i].toStdString().find("Recycle Bin") + 12));
		p.drawText(textposition, filename);
		y += 20.f;
	}
}

void RecycleBinView::mouseReleaseEvent(QMouseEvent* e)
{
	QPointF pos = e->localPos().toPoint();
	Qt::MouseButton B = e->button();
	if (B == Qt::LeftButton)
	{
		int selected = -1;
		float min_dist = (1 << 31) - 1;
		for (int i = 0; i < m_files.size(); i++)
		{
			float loc_y = 50.f + 20.f * i;
			if (abs(loc_y - pos.y()) < min_dist)
			{
				min_dist = abs(loc_y - pos.y());
				selected = i;
			}
		}
		if (m_colors[selected] == 1)
		{
			m_colors[selected] = 0;
		}
		else
		{
			m_colors[selected] = 1;
		}
	}
	update();
}

void RecycleBinView::UpdateFiles()
{
	QString requestIndex = QString::fromStdString(std::to_string(static_cast<int> (Requests::VIEWTRASH)) + ' ');
	QString message = requestIndex + m_username;
	QString filename = m_con->request(message);
	std::cout << filename.toStdString();
	std::cout << "intru in functie!\n";
	while (filename != QString::fromStdString(m_eot))
	{
		std::cout << "afisez o fila\n";
		m_files.push_back(correctslashes(filename));
		m_colors.push_back(0);
		filename = m_con->request("next file");
	}
	std::cout << "ies din functie\n";
	update();
}

void RecycleBinView::ResetFiles()
{
	m_files.clear();
	m_colors.clear();
}

RecycleBinView::~RecycleBinView()
{
	delete ui;
}

void RecycleBinView::on_pushButton_released()
{
	for (int i = 0; i < m_files.size(); i++)
	{
		if (m_colors[i] == 1)
		{
			QString requestIndex = QString::fromStdString(std::to_string(static_cast<int> (Requests::RESTOREFILE)) + ' ');
			QString filename = QString::fromStdString(m_files[i].toStdString().substr(m_files[i].toStdString().find("Recycle Bin") + 12));
			QString message = requestIndex + m_username + ' ' + filename;
			m_con->request(message);
		}
	}
	*m_finished = true;
	*m_subWindowOpen = false;
	this->close();
}


void RecycleBinView::on_pushButton_2_released()
{
	for (int i = 0; i < m_files.size(); i++)
	{
		if (m_colors[i] == 1)
		{
			QString requestIndex = QString::fromStdString(std::to_string((int)Requests::PERMANENTLYREMOVEFILE) + ' ');
			QString filename = QString::fromStdString(m_files[i].toStdString().substr(m_files[i].toStdString().find("Recycle Bin") + 12));
			QString message = requestIndex + m_username + ' ' + filename;
			m_con->request(message);
		}
	}
	*m_finished = true;
	*m_subWindowOpen = false;
	this->close();
}

void RecycleBinView::setFolderpath(std::string folderpath)
{
	this->m_folderpath = folderpath;
}


void RecycleBinView::setFinished(std::atomic<bool>& finished)
{
	this->m_finished = &finished;
}

void RecycleBinView::setSubWindowOpen(bool& subWindowOpen)
{
	this->m_subWindowOpen = &subWindowOpen;
}

void RecycleBinView::closeEvent(QCloseEvent* event)
{
	*m_finished = true;
	*m_subWindowOpen = false;
}

