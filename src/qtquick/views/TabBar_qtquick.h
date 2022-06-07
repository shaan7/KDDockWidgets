/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

/**
 * @file
 * @brief Implements a QTabWidget derived class with support for docking and undocking
 * KDockWidget::DockWidget as tabs .
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#ifndef KD_TABBAR_QUICK_P_H
#define KD_TABBAR_QUICK_P_H
#pragma once

#include "View_qtquick.h"
#include "views/TabBar.h"

#include <QPointer>
#include <QHash>

namespace KDDockWidgets::Controllers {
class TabBar;
}

namespace KDDockWidgets::Views {

class DockWidget;
class TabWidget;

class DOCKS_EXPORT TabBar_qtquick
    : public View_qtquick,
      public TabBar
{
    Q_OBJECT
    Q_PROPERTY(QQuickItem *tabBarQmlItem READ tabBarQmlItem WRITE setTabBarQmlItem NOTIFY tabBarQmlItemChanged)
public:
    explicit TabBar_qtquick(Controllers::TabBar *controller, QQuickItem *parent = nullptr);
    int tabAt(QPoint localPos) const override;

    QQuickItem *tabBarQmlItem() const;
    void setTabBarQmlItem(QQuickItem *);

    QString text(int index) const override;
    QRect rectForTab(int index) const override;

    void moveTabTo(int from, int to) override;
    Controllers::DockWidget *currentDockWidget() const override;
    bool tabsAreMovable() const override;

Q_SIGNALS:
    void tabBarQmlItemChanged();

protected:
    bool event(QEvent *ev) override;

private:
    QHash<int, QQuickItem *> qmlTabs() const;
    QQuickItem *tabAt(int index) const;
    QQuickItem *listView() const;
    QPointer<QQuickItem> m_tabBarQmlItem;
    Controllers::TabBar *const m_controller;
};
}

#endif
