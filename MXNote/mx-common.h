#ifndef COMMON_H
#define COMMON_H


#ifdef _DEBUG

#define APP_DATA_FOLDER  QCoreApplication::applicationDirPath()

#else

//QStringList folders = QStandardPaths::standardLocations(QStandardPaths::AppConfigLocation);
#define APP_DATA_FOLDER  QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation)

#endif



#endif // COMMON_H
