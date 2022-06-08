#pragma once
#include <qfilesystemmodel.h>

class OnedriveFileSystemModel : public QFileSystemModel {
private:
	std::vector <std::string>* m_unsynched;
	std::vector <std::string>* m_trashed;
public:
	QVariant data(const QModelIndex& index, int role) const;
	void setUnsynched(std::vector <std::string>& unsynched);
	void setTrashed(std::vector <std::string>& trashed);
};