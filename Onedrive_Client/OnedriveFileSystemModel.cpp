#pragma once
#include "OnedriveFileSystemModel.h"
#include <filesystem>
#include "Utilites.h"
#include <iostream>

QVariant OnedriveFileSystemModel::data(const QModelIndex& index, int role) const {

	if (role == Qt::BackgroundColorRole) {
		if (index.siblingAtColumn(2).data() == "File Folder")
		{
			return QColor(255, 245, 204);
		}
		else
		{
			std::string relativepath = this->fileInfo(index).absoluteFilePath().toStdString();
			std::string abspath = correctslashes(std::filesystem::absolute(relativepath).string());
			std::cout << "model path " << abspath << '\n';
			if (std::find(m_unsynched->begin(), m_unsynched->end(), abspath) != m_unsynched->end())
				return QColor(255, 200, 200);
			if (std::find(m_trashed->begin(), m_trashed->end(), abspath) != m_trashed->end())
				return QColor(255, 230, 230);
		}
	}
	return QFileSystemModel::data(index, role);
}

void OnedriveFileSystemModel::setUnsynched(std::vector <std::string>& unsynched)
{
	this->m_unsynched = &unsynched;
}

void OnedriveFileSystemModel::setTrashed(std::vector <std::string>& trashed)
{
	this->m_trashed = &trashed;
}