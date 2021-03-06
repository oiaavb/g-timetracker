/**
 ** This file is part of the G-TimeTracker project.
 ** Copyright 2015-2016 Nikita Krupenko <krnekit@gmail.com>.
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/

pragma Singleton
import QtQuick 2.0
import Qt.labs.settings 1.0

Item {
    id: settings

    property bool isConfirmationsEnabled: true
    property bool isCheckForUpdates: true
    property string lastVersion
    property bool isShowChangeLog: true
    property bool isAutoSync: true
    property int syncCacheSize: 10
    property int syncCacheTimeout: 3600
    property url syncPath
    property url dataPath

    Settings {
        property alias confirmationsEnabled: settings.isConfirmationsEnabled
        property alias checkForUpdates: settings.isCheckForUpdates
        property alias lastVersion: settings.lastVersion
        property alias showChangeLog: settings.isShowChangeLog

        category: "main"
    }

    Settings {
        property alias autoSync: settings.isAutoSync
        property alias syncCacheSize: settings.syncCacheSize
        property alias syncCacheTimeout: settings.syncCacheTimeout
        property alias syncPath: settings.syncPath
        property alias dataPath: settings.dataPath

        category: "sync"
    }
}
