//=============================================================================================================
/**
* @file     test_spectral_connectivity.cpp
* @author   Daniel Strohmeier <daniel.strohmeier@tu-ilmenau.de>;
*           Matti Hamalainen <msh@nmr.mgh.harvard.edu>
* @version  1.0
* @date     May, 2018
*
* @section  LICENSE
*
* Copyright (C) 2018, Daniel Strohmeier and Matti Hamalainen. All rights reserved.
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
* @brief    The spectral connectivity test implementation
*
*/


//*************************************************************************************************************
//=============================================================================================================
// INCLUDES
//=============================================================================================================

#include <iostream>
#include <mne/mne.h>
#include <utils/ioutils.h>
#include "connectivity/metrics/coherence.h"
#include "connectivity/metrics/imagcoherence.h"
#include "connectivity/metrics/phaselockingvalue.h"
#include "connectivity/metrics/phaselagindex.h"
#include "connectivity/metrics/unbiasedsquaredphaselagindex.h"


//*************************************************************************************************************
//=============================================================================================================
// QT INCLUDES
//=============================================================================================================

#include <QtTest>


//*************************************************************************************************************
//=============================================================================================================
// Eigen INCLUDES
//=============================================================================================================

#include <Eigen/Core>


//*************************************************************************************************************
//=============================================================================================================
// USED NAMESPACES
//=============================================================================================================

using namespace Eigen;
using namespace CONNECTIVITYLIB;
using namespace UTILSLIB;


//=============================================================================================================
/**
* DECLARE CLASS TestSpectralConnectivity
*
* @brief The TestSpectralConnectivity class provides spectral connectivity tests
*
*/
class TestSpectralConnectivity: public QObject
{
    Q_OBJECT

public:
    TestSpectralConnectivity();

private slots:
    void initTestCase();
    void spectralConnectivityCoherence();
    void spectralConnectivityImagCoherence();
    void spectralConnectivityPLV();
    void spectralConnectivityPLI();
    void spectralConnectivityPLI2();
    void spectralConnectivityWPLI();
    void spectralConnectivityWPLI2();
    void cleanupTestCase();

private:
    void compareConnectivity();
    double epsilon;
    RowVectorXd m_ConnectivityOutput;
    RowVectorXd m_RefConnectivityOutput;
};


//*************************************************************************************************************

TestSpectralConnectivity::TestSpectralConnectivity()
: epsilon(0.000001)
{
}


//*************************************************************************************************************

void TestSpectralConnectivity::TestSpectralConnectivity()
{

}


//*************************************************************************************************************

void TestSpectralConnectivity::spectralConnectivityCoherence()
{
    //*********************************************************************************************************
    // Load Data
    //*********************************************************************************************************

    inputTrials = MatrixXd();
    QString dataFileName(QDir::currentPath()+"/mne-cpp-test-data/MEG/sample/data_spectral_connectivity.txt");
    IOUtils::read_eigen_matrix(inputTrials, dataFileName);
    int iNTrials = inputTrials.rows() / 2;
    int iNfft = inputTrials.cols();
    QString sWindowType = "hanning";

    QList<MatrixXd> matDataList;
    for (int i = 0; i < iNTrials; ++i)
    {
        matDataList.append(inputTrials.middleRows(i * 2, 2));
    }

    //*********************************************************************************************************
    // Compute Connectivity
    //*********************************************************************************************************

    QVector<MatrixXd> Coh = Coherence::computeCoherence(matDataList, iNfft, sWindowType);
    m_ConnectivityOutput = Coh.at(0).row(1);

    //*********************************************************************************************************
    // Load MNE-PYTHON Results As Reference
    //*********************************************************************************************************

    refConnectivity = MatrixXd();
    QString refFileName(QDir::currentPath()+"/mne-cpp-test-data/Result/Connectivity/ref_spectral_connectivity_coh.txt");
    IOUtils::read_eigen_matrix(refConnectivity, refFileName);
    m_RefConnectivityOutput = refConnectivity.row(0);

    //*********************************************************************************************************
    // Compare Connectivity
    //*********************************************************************************************************

    compareConnectivity();
}


//*************************************************************************************************************

void TestSpectralConnectivity::spectralConnectivityImagCoherence()
{
    //*********************************************************************************************************
    // Load Data
    //*********************************************************************************************************

    inputTrials = MatrixXd();
    QString dataFileName(QDir::currentPath()+"/mne-cpp-test-data/MEG/sample/data_spectral_connectivity.txt");
    IOUtils::read_eigen_matrix(inputTrials, dataFileName);
    int iNTrials = inputTrials.rows() / 2;
    int iNfft = inputTrials.cols();
    QString sWindowType = "hanning";

    QList<MatrixXd> matDataList;
    for (int i = 0; i < iNTrials; ++i)
    {
        matDataList.append(inputTrials.middleRows(i * 2, 2));
    }

    //*********************************************************************************************************
    // Compute Connectivity
    //*********************************************************************************************************

    QVector<MatrixXd> ImagCoh = ImagCoherence::computeImagCoherence(matDataList, iNfft, sWindowType);
    m_ConnectivityOutput = ImagCoh.at(0).row(1);

    //*********************************************************************************************************
    // Load MNE-PYTHON Results As Reference
    //*********************************************************************************************************

    refConnectivity = MatrixXd();
    QString refFileName(QDir::currentPath()+"/mne-cpp-test-data/Result/Connectivty/ref_spectral_connectivity_icoh.txt");
    IOUtils::read_eigen_matrix(refConnectivity, refFileName);
    m_RefConnectivityOutput = refConnectivity.row(0);

    //*********************************************************************************************************
    // Compare Connectivity
    //*********************************************************************************************************

    compareConnectivity();
}


//*************************************************************************************************************

void TestSpectralConnectivity::spectralConnectivityPLV()
{
    //*********************************************************************************************************
    // Load Data
    //*********************************************************************************************************

    inputTrials = MatrixXd();
    QString dataFileName(QDir::currentPath()+"/mne-cpp-test-data/MEG/sample/data_spectral_connectivity.txt");
    IOUtils::read_eigen_matrix(inputTrials, dataFileName);
    int iNTrials = inputTrials.rows() / 2;
    int iNfft = inputTrials.cols();
    QString sWindowType = "hanning";

    QList<MatrixXd> matDataList;
    for (int i = 0; i < iNTrials; ++i)
    {
        matDataList.append(inputTrials.middleRows(i * 2, 2));
    }

    //*********************************************************************************************************
    // Compute Connectivity
    //*********************************************************************************************************

    QVector<MatrixXd> PLV = PhaseLockingValue::computePLV(matDataList, iNfft, sWindowType);
    m_ConnectivityOutput = PLV.at(0).row(1);

    //*********************************************************************************************************
    // Load MNE-PYTHON Results As Reference
    //*********************************************************************************************************

    refConnectivity = MatrixXd();
    QString refFileName(QDir::currentPath()+"/mne-cpp-test-data/Result/Connectivty/ref_spectral_connectivity_plv.txt");
    IOUtils::read_eigen_matrix(refConnectivity, refFileName);
    m_RefConnectivityOutput = refConnectivity.row(0);

    //*********************************************************************************************************
    // Compare Connectivity
    //*********************************************************************************************************

    compareConnectivity();
}


//*************************************************************************************************************

void TestSpectralConnectivity::spectralConnectivityPLI()
{
    //*********************************************************************************************************
    // Load Data
    //*********************************************************************************************************

    inputTrials = MatrixXd();
    QString dataFileName(QDir::currentPath()+"/mne-cpp-test-data/MEG/sample/data_spectral_connectivity.txt");
    IOUtils::read_eigen_matrix(inputTrials, dataFileName);
    int iNTrials = inputTrials.rows() / 2;
    int iNfft = inputTrials.cols();
    QString sWindowType = "hanning";

    QList<MatrixXd> matDataList;
    for (int i = 0; i < iNTrials; ++i)
    {
        matDataList.append(inputTrials.middleRows(i * 2, 2));
    }

    //*********************************************************************************************************
    // Compute Connectivity
    //*********************************************************************************************************

    QVector<MatrixXd> PLI = PhaseLagIndex::computePLI(matDataList, iNfft, sWindowType);
    m_ConnectivityOutput = PLI.at(0).row(1);

    //*********************************************************************************************************
    // Load MNE-PYTHON Results As Reference
    //*********************************************************************************************************

    refConnectivity = MatrixXd();
    QString refFileName(QDir::currentPath()+"/mne-cpp-test-data/Result/Connectivty/ref_spectral_connectivity_pli.txt");
    IOUtils::read_eigen_matrix(refConnectivity, refFileName);
    m_RefConnectivityOutput = refConnectivity.row(0);

    //*********************************************************************************************************
    // Compare Connectivity
    //*********************************************************************************************************

    compareConnectivity();
}


//*************************************************************************************************************

void TestSpectralConnectivity::spectralConnectivityPLI2()
{
    //*********************************************************************************************************
    // Load Data
    //*********************************************************************************************************

    inputTrials = MatrixXd();
    QString dataFileName(QDir::currentPath()+"/mne-cpp-test-data/MEG/sample/data_spectral_connectivity.txt");
    IOUtils::read_eigen_matrix(inputTrials, dataFileName);
    int iNTrials = inputTrials.rows() / 2;
    int iNfft = inputTrials.cols();
    QString sWindowType = "hanning";

    QList<MatrixXd> matDataList;
    for (int i = 0; i < iNTrials; ++i)
    {
        matDataList.append(inputTrials.middleRows(i * 2, 2));
    }

    //*********************************************************************************************************
    // Compute Connectivity
    //*********************************************************************************************************

    QVector<MatrixXd> PLI2 = UnbiasedSquaredPhaseLagIndex::computeUnbiasedSquaredPLI(matDataList, iNfft, sWindowType);
    m_ConnectivityOutput = PLI2.at(0).row(1);

    //*********************************************************************************************************
    // Load MNE-PYTHON Results As Reference
    //*********************************************************************************************************

    refConnectivity = MatrixXd();
    QString refFileName(QDir::currentPath()+"/mne-cpp-test-data/Result/Connectivty/ref_spectral_connectivity_pli.txt");
    IOUtils::read_eigen_matrix(refConnectivity, refFileName);
    m_RefConnectivityOutput = refConnectivity.row(0);

    //*********************************************************************************************************
    // Compare Connectivity
    //*********************************************************************************************************

    compareConnectivity();
}


//*************************************************************************************************************

void TestSpectralConnectivity::compareConnectivity()
{
    //*********************************************************************************************************
    // Compare Spectral Connectvitity Result to MNE-PYTHON
    //*********************************************************************************************************

    printf(">>>>>>>>>>>>>>>>>>>>>>>>> Compare Spectral Connectivities >>>>>>>>>>>>>>>>>>>>>>>>>\n");

    QVERIFY( m_ConnectivityOutput.cols() == m_RefConnectivityOutput.cols() );
    for (int i = 0; i < m_ConnectivityOutput.cols(); ++i)
    {
        QVERIFY( (m_ConnectivityOutput(i) - m_RefConnectivityOutput(i)) / m_RefConnectivityOutput(i) < epsilon );
    }

    printf("<<<<<<<<<<<<<<<<<<<<<<<<< Compare Spectral Connectivities Finished <<<<<<<<<<<<<<<<<<<<<<<<<\n");
}


//*************************************************************************************************************

void TestSpectralConnectivity::cleanupTestCase()
{
}


//*************************************************************************************************************
//=============================================================================================================
// MAIN
//=============================================================================================================

QTEST_APPLESS_MAIN(TestSpectralConnectivity)
