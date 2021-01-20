//=============================================================================================================
/**
 * @file     spectrumsetupwidget.cpp
 * @author   Christoph Dinh <chdinh@nmr.mgh.harvard.edu>;
 *           Lorenz Esch <lesch@mgh.harvard.edu>
 * @since    0.1.0
 * @date     February, 2013
 *
 * @section  LICENSE
 *
 * Copyright (C) 2013, Christoph Dinh, Lorenz Esch. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that
 * the following conditions are met:
 *     * Redistributions of source code must retain the above copyright notice, this list of conditions and the
 *       following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and
 *       the following disclaimer in the documentation and/or other materials provided with the distribution.
 *     * Neither the name of MNE-CPP authors nor the names of its contributors may be used
 *       to endorse or promote products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * @brief    Definition of the SpectrumSetupWidget class.
 *
 */

//=============================================================================================================
// INCLUDES
//=============================================================================================================

#include "spectrumsetupwidget.h"

#include "../spectrum.h"

#include "disp/viewers/bandpowersettingsview.h"
#include "disp/viewers/arsettingsview.h"

//=============================================================================================================
// QT INCLUDES
//=============================================================================================================

#include <QDebug>
#include <QTabWidget>

//=============================================================================================================
// USED NAMESPACES
//=============================================================================================================

using namespace SPECTRUMPLUGIN;
using namespace DISPLIB;

//=============================================================================================================
// DEFINE MEMBER METHODS
//=============================================================================================================

SpectrumSetupWidget::SpectrumSetupWidget(Spectrum* pSpectrum, QWidget *parent)
    : QWidget(parent)
    , m_pSpectrum(pSpectrum)
{
    ui.setupUi(this);

    BandPowerSettingsView* pBandPowerSettingsView = new BandPowerSettingsView(QString("MNESCAN/%1/").arg(m_pSpectrum->getName()),
                                                                              512, 10, 20, QString::fromStdString("AR"), 1, -1);
    ARSettingsView* pARSettingsView = new ARSettingsView(QString("MNESCAN/%1/").arg(m_pSpectrum->getName()));

    QVBoxLayout* settingsLayout = new QVBoxLayout;

    QTabWidget* settingsTab = new QTabWidget;

    settingsTab->addTab(pBandPowerSettingsView, "Spectrum Settings");
    settingsTab->addTab(pARSettingsView, "AR Settings");

    settingsLayout->addWidget(settingsTab);

    ui.m_qGroupBox_BandPowerOptions->setLayout(settingsLayout);

    connect(pBandPowerSettingsView,&BandPowerSettingsView::changeMinMax,m_pSpectrum,&Spectrum::changeMinMaxFrequency);
    connect(pBandPowerSettingsView,&BandPowerSettingsView::changeMethod,m_pSpectrum,&Spectrum::changeSpectrumMethod);
    connect(pBandPowerSettingsView,&BandPowerSettingsView::changeIntervallLength,m_pSpectrum,&Spectrum::changeIntervallLengthFactor);
    connect(pBandPowerSettingsView,&BandPowerSettingsView::changeDetrend,m_pSpectrum,&Spectrum::changeDetrendMethod);
    connect(pBandPowerSettingsView,&BandPowerSettingsView::changeBins,m_pSpectrum,&Spectrum::changeSpectrumBins);

    pBandPowerSettingsView->emitSignals();

    connect(pARSettingsView, &ARSettingsView::changeAROrder,m_pSpectrum,&Spectrum::changeAROrder);
    connect(pARSettingsView, &ARSettingsView::changeARNumEvaluationPoints,m_pSpectrum,&Spectrum::changeARNumEvaluationPoints);

    pARSettingsView->emitSignals();
}

//=============================================================================================================

SpectrumSetupWidget::~SpectrumSetupWidget()
{
}
