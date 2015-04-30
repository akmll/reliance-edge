/*             ----> DO NOT REMOVE THE FOLLOWING NOTICE <----

                   Copyright (c) 2014-2015 Datalight, Inc.
                       All Rights Reserved Worldwide.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; use version 2 of the License.

    This program is distributed in the hope that it will be useful,
    but "AS-IS," WITHOUT ANY WARRANTY; without even the implied warranty
    of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/
/*  Businesses and individuals that for commercial or other reasons cannot
    comply with the terms of the GPLv2 license may obtain a commercial license
    before incorporating Reliance Edge into proprietary software for
    distribution in any form.  Visit http://www.datalight.com/reliance-edge for
    more information.
*/
#include "configwindow.h"
#include "ui_configwindow.h"
#include "allsettings.h"
#include "validators.h"
#include "output.h"

ConfigWindow::ConfigWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConfigWindow)
{
    ui->setupUi(this);

    // Instantiate allSettings

    // "General" tab
    allSettings.cbsReadonly = new CbSetting(macroNameReadonly, false, emptyBoolValidator, ui->cbReadonly);
    allSettings.rbtnsUsePosix = new RbtnSetting(macroNameUsePosix, true, validateUsePosixApi, ui->rbtnUsePosix, ui->wbtnApiRbtns);
    allSettings.rbtnsUseFse = new RbtnSetting(macroNameUseFse, false, validateUseFseApi, ui->rbtnUseFse, ui->wbtnApiRbtns);
    allSettings.cbsPosixFormat = new CbSetting(macroNamePosixFormat, true, emptyBoolValidator, ui->cbPosixFormat);
    allSettings.cbsPosixLink = new CbSetting(macroNamePosixLink, true, emptyBoolValidator, ui->cbPosixLink);
    allSettings.cbsPosixUnlink = new CbSetting(macroNamePosixUnlink, true, emptyBoolValidator, ui->cbPosixUnlink);
    allSettings.cbsPosixMkdir = new CbSetting(macroNamePosixMkdir, true, emptyBoolValidator, ui->cbPosixMkdir);
    allSettings.cbsPosixRmdir = new CbSetting(macroNamePosixRmdir, true, emptyBoolValidator, ui->cbPosixRmDir);
    allSettings.cbsPosixRename = new CbSetting(macroNamePosixRename, false, emptyBoolValidator, ui->cbPosixRename);
    allSettings.cbsPosixAtomicRename = new CbSetting(macroNamePosixRenameAtomic, false, emptyBoolValidator, ui->cbPosixAtomicRename);
    allSettings.cbsPosixFtruncate = new CbSetting(macroNamePosixFtruncate, true, emptyBoolValidator, ui->cbPosixFtruncate);
    allSettings.cbsPosixDirOps = new CbSetting(macroNamePosixDirOps, true, emptyBoolValidator, ui->cbPosixDirOps);
    allSettings.sbsMaxNameLen = new SbSetting(macroNameMaxNameLen, 12, validateMaxNameLen, ui->sbFileNameLen, ui->wbtnFileNameLen);
    allSettings.pssPathSepChar = new PathSepSetting(macroNamePathSepChar, "/", validatePathSepChar, ui->cmbPathChar, ui->lePathCharCustom, ui->wbtnPathChar);
    allSettings.cbsFseTruncate = new CbSetting(macroNameFseTruncate, true, emptyBoolValidator, ui->cbFseTruncate);
    allSettings.sbsTaskCount = new SbSetting(macroNameTaskCount, 10, validateTaskCount, ui->sbTaskCount, ui->wbtnTaskCount);
    allSettings.sbsHandleCount = new SbSetting(macroNameHandleCount, 10, validateHandleCount, ui->sbHandleCount, ui->wbtnHandleCount);
    allSettings.cbsFseGetMask = new CbSetting(macroNameFseGetMask, true, emptyBoolValidator, ui->cbFseGetMask);
    allSettings.cbsFseSetMask = new CbSetting(macroNameFseSetMask, true, emptyBoolValidator, ui->cbFseSetMask);
    allSettings.cbsDebugEnableOutput = new CbSetting(macroNameDebugEnableOutput, false, emptyBoolValidator, ui->cbEnableOutput);
    allSettings.cbsDebugProcesAsserts = new CbSetting(macroNameDebugProcesAsserts, false, emptyBoolValidator, ui->cbProcessAsserts);

    // "Volumes" tab (Note: most settings handled
    // by VolumeSettings
    allSettings.cmisBlockSize = new CmbIntSetting(macroNameBlockSize, 512, validateBlockSize, ui->cmbBlockSize, ui->wbtnBlockSize);

    // "Data Storage" tab
    allSettings.cmssByteOrder = new CmbStrSetting(macroNameByteOrder, "Little endian", validateByteOrder, ui->cmbByteOrder, ui->wbtnByteOrder);
    allSettings.cmisNativeAlignment = new CmbIntSetting(macroNameNativeAlignment, 4, validateAlignmentSize, ui->cmbAlignmentSize, ui->wbtnAlignmentSize);
    allSettings.cmssCrc = new CmbStrSetting(macroNameCrc, "Slice by 8 - largest, fastest", validateCrc, ui->cmbCrc, ui->wbtnCrc);
    allSettings.cbsInodeCount = new CbSetting(macroNameInodeCount, true, emptyBoolValidator, ui->cbInodeBlockCount);
    allSettings.cbsInodeTimestamps = new CbSetting(macroNameInodeTimestamps, true, emptyBoolValidator, ui->cbInodeTimestamps);
    allSettings.cbsUpdateAtime = new CbSetting(macroNameUpdateAtime, false, emptyBoolValidator, ui->cbUpdateAtime);
    allSettings.sbsDirectPtrs = new SbSetting(macroNameDirectPtrs, 4, validateDirectPointers, ui->sbDirectPointers, ui->wbtnDirectPointers);
    allSettings.sbsIndirectPtrs = new SbSetting(macroNameIndirectPtrs, 32, validateIndirectPointers, ui->sbIndirectPointers, ui->wbtnIndirectPointers);

    // "Memory" tab
    allSettings.sbsAllocatedBuffers = new SbSetting(macroNameAllocatedBuffers, 8, validateAllocatedBuffers, ui->sbAllocatedBuffers, ui->wbtnAllocatedBuffers);
    allSettings.lesMemcpy = new LeSetting(macroNameMemcpy, cstdMemcpy, emptyStringValidator, ui->leMemcpy);
    allSettings.lesMemmov = new LeSetting(macroNameMemmov, cstdMemmov, emptyStringValidator, ui->leMemmov);
    allSettings.lesMemset = new LeSetting(macroNameMemset, cstdMemset, emptyStringValidator, ui->leMemset);
    allSettings.lesMemcmp = new LeSetting(macroNameMemcmp, cstdMemcmp, emptyStringValidator, ui->leMemcmp);
    allSettings.lesStrlen = new LeSetting(macroNameStrlen, cstdStrlen, emptyStringValidator, ui->leStrlen);
    allSettings.lesStrcmp = new LeSetting(macroNameStrcmp, cstdStrcmp, emptyStringValidator, ui->leStrcmp);
    allSettings.lesStrncmp = new LeSetting(macroNameStrncmp, cstdStrncmp, emptyStringValidator, ui->leStrncmp);
    allSettings.lesStrncpy = new LeSetting(macroNameStrncpy, cstdStrncpy, emptyStringValidator, ui->leStrncpy);
    allSettings.lesInclude = new LeSetting("", cstdStringH, validateMemInclude, ui->leIncludeFile, ui->wbtnIncludeFile);

    // "Transaction Points" tab
    allSettings.cbsTrManual = new CbSetting(macroNameTrManual, false, validateTransactManual,ui->cbTransactManual, ui->wbtnTransactManual);
    allSettings.cbsTrFileCreat = new CbSetting(macroNameTrFileCreat, true, emptyBoolValidator, ui->cbTransactFileCreate);
    allSettings.cbsTrDirCreat = new CbSetting(macroNameTrDirCreat, true, emptyBoolValidator, ui->cbTransactDirCreate);
    allSettings.cbsTrRename = new CbSetting(macroNameTrRename, true, emptyBoolValidator, ui->cbTransactRename);
    allSettings.cbsTrLink = new CbSetting(macroNameTrLink, true, emptyBoolValidator, ui->cbTransactLink);
    allSettings.cbsTrUnlink = new CbSetting(macroNameTrUnlink, true, emptyBoolValidator, ui->cbTransactUnlink);
    allSettings.cbsTrWrite = new CbSetting(macroNameTrWrite, false, emptyBoolValidator, ui->cbTransactWrite);
    allSettings.cbsTrTruncate = new CbSetting(macroNameTrTruncate, false, emptyBoolValidator, ui->cbTransactTruncate);
    allSettings.cbsTrSync = new CbSetting(macroNameTrSync, true, emptyBoolValidator, ui->cbTransactFSync);
    allSettings.cbsTrClose = new CbSetting(macroNameTrClose, true, emptyBoolValidator, ui->cbTransactClose);
    allSettings.cbsTrVolFull = new CbSetting(macroNameTrVolFull, true, validateTransactVolFull, ui->cbTransactVolFull, ui->wbtnTransactVolFull);
    allSettings.cbsTrUmount = new CbSetting(macroNameTrUmount, true, emptyBoolValidator, ui->cbTransactVolUnmount);

    allSettings.cbsInodeCount->notifyList.append(allSettings.sbsDirectPtrs);
    allSettings.cbsInodeCount->notifyList.append(allSettings.sbsIndirectPtrs);
    allSettings.cbsInodeTimestamps->notifyList.append(allSettings.sbsDirectPtrs);
    allSettings.cbsInodeTimestamps->notifyList.append(allSettings.sbsIndirectPtrs);
    allSettings.rbtnsUsePosix->notifyList.append(allSettings.sbsDirectPtrs);
    allSettings.rbtnsUsePosix->notifyList.append(allSettings.sbsIndirectPtrs);
    allSettings.cmisBlockSize->notifyList.append(allSettings.sbsDirectPtrs);
    allSettings.cmisBlockSize->notifyList.append(allSettings.sbsIndirectPtrs);
    allSettings.sbsIndirectPtrs->notifyList.append(allSettings.sbsDirectPtrs);
    allSettings.sbsDirectPtrs->notifyList.append(allSettings.sbsIndirectPtrs);

    // The following settings  are dependent
    allSettings.cbsInodeCount->notifyList.append(allSettings.sbsAllocatedBuffers);
    allSettings.cbsInodeTimestamps->notifyList.append(allSettings.sbsAllocatedBuffers);
    allSettings.rbtnsUsePosix->notifyList.append(allSettings.sbsAllocatedBuffers);
    allSettings.cmisBlockSize->notifyList.append(allSettings.sbsAllocatedBuffers);
    allSettings.sbsIndirectPtrs->notifyList.append(allSettings.sbsAllocatedBuffers);
    allSettings.sbsDirectPtrs->notifyList.append(allSettings.sbsAllocatedBuffers);
    allSettings.rbtnsUsePosix->notifyList.append(allSettings.sbsAllocatedBuffers);
    allSettings.cbsPosixRename->notifyList.append(allSettings.sbsAllocatedBuffers);
    allSettings.cbsPosixAtomicRename->notifyList.append(allSettings.sbsAllocatedBuffers);

    // Simulate toggling to init which transaction flags
    // are available
    rbtnUsePosix_toggled(allSettings.rbtnsUsePosix->GetValue());
    ui->cbPosixAtomicRename->setEnabled(allSettings.cbsPosixRename->GetValue());

    // Must be initialized after allSettings.cmisBlockSize
    volumeSettings = new VolumeSettings(ui->lePathPrefix,
                                        ui->cmbSectorSize,
                                        ui->sbVolSize,
                                        ui->labelVolSizeBytes,
                                        ui->sbInodeCount,
                                        ui->cmbAtomicWrite,
                                        ui->btnAddVol,
                                        ui->btnRemoveCurrVol,
                                        ui->listVolumes,
                                        ui->wbtnVolumeCtrls,
                                        ui->wbtnPathPrefix,
                                        ui->wbtnSectorSize,
                                        ui->wbtnVolSize,
                                        ui->wbtnInodeCount,
                                        ui->wbtnAtomicWrite);

    wbtns.append(ui->wbtnTransactVolFull);
    wbtns.append(ui->wbtnTransactManual);
    wbtns.append(ui->wbtnAllocatedBuffers);
    wbtns.append(ui->wbtnIndirectPointers);
    wbtns.append(ui->wbtnDirectPointers);
    wbtns.append(ui->wbtnCrc);
    wbtns.append(ui->wbtnAlignmentSize);
    wbtns.append(ui->wbtnByteOrder);
    wbtns.append(ui->wbtnVolumeCtrls);
    wbtns.append(ui->wbtnSectorSize);
    wbtns.append(ui->wbtnVolSize);
    wbtns.append(ui->wbtnAtomicWrite);
    wbtns.append(ui->wbtnInodeCount);
    wbtns.append(ui->wbtnPathPrefix);
    wbtns.append(ui->wbtnBlockSize);
    wbtns.append(ui->wbtnHandleCount);
    wbtns.append(ui->wbtnTaskCount);
    wbtns.append(ui->wbtnPathChar);
    wbtns.append(ui->wbtnFileNameLen);
    wbtns.append(ui->wbtnApiRbtns);
    wbtns.append(ui->wbtnIncludeFile);

    for(int i = 0; i < wbtns.count(); i++)
    {
        connect(wbtns[i], SIGNAL(clicked()),
                this, SIGNAL(warningBtnClicked()));
    }
    connect(ui->cbReadonly, SIGNAL(toggled(bool)),
            this, SLOT(cbReadonly_toggled(bool)));
    connect(ui->rbtnUsePosix, SIGNAL(toggled(bool)),
            this, SLOT(rbtnUsePosix_toggled(bool)));
    connect(ui->cbPosixRename, SIGNAL(toggled(bool)),
            this, SLOT(cbPosixRename_toggled(bool)));
    connect(ui->cbPosixMkdir, SIGNAL(toggled(bool)),
            this, SLOT(cbPosixMkdir_toggled(bool)));
    connect(ui->cbPosixLink, SIGNAL(toggled(bool)),
            this, SLOT(cbPosixLink_toggled(bool)));
    connect(ui->cbPosixUnlink, SIGNAL(toggled(bool)),
            this, SLOT(cbPosixUnlink_toggled(bool)));
    connect(ui->cbPosixFtruncate, SIGNAL(toggled(bool)),
            this, SLOT(cbPosixFtruncate_toggled(bool)));
    connect(ui->cbFseTruncate, SIGNAL(toggled(bool)),
            this, SLOT(cbFseTruncate_toggled(bool)));
    connect(ui->cbInodeTimestamps, SIGNAL(toggled(bool)),
            this, SLOT(cbInodeTimestamps_toggled(bool)));
    connect(ui->rbtnMemUseCStd, SIGNAL(toggled(bool)),
            this, SLOT(rbtnMemUseCStd_toggled(bool)));
    connect(ui->rbtnMemUseReliance, SIGNAL(toggled(bool)),
            this, SLOT(rbtnMemUseReliance_toggled(bool)));
    connect(ui->rbtnMemCustomize, SIGNAL(toggled(bool)),
            this, SLOT(rbtnMemCustomize_toggled(bool)));
    connect(ui->cbTransactManual, SIGNAL(toggled(bool)),
            this, SLOT(cbTransactManual_toggled(bool)));

    // Forwarded signals
    connect(ui->actionSave, SIGNAL(triggered()),
            this, SIGNAL(saveClicked()));
    connect(ui->actionLoad, SIGNAL(triggered()),
            this, SIGNAL(loadClicked()));

    // Hide settings for unused API
    if(allSettings.rbtnsUsePosix->GetValue())
    {
        ui->frameFseOps->setVisible(false);
    }
    else
    {
        ui->framePosixOps->setVisible(false);
    }

    // Not controlled by a Setting object, so set it here.
    ui->rbtnMemUseCStd->setChecked(true);

    limitReporter = new LimitReporter(ui->lFsizeBytes, ui->lVsizeBytes);
}

ConfigWindow::~ConfigWindow()
{
    delete ui;
    delete volumeSettings;
    volumeSettings = NULL;

    AllSettings::DeleteAll();

    delete limitReporter;
}

void ConfigWindow::SetMemRbtnSelection(MemFnSet mfs)
{
    switch(mfs)
    {
        case UseCStd:
            ui->rbtnMemUseCStd->setChecked(true);
            break;

        case UseReliance:
            ui->rbtnMemUseReliance->setChecked(true);
            break;

        case Customize:
            ui->rbtnMemCustomize->setChecked(true);
            break;
    }
}

void ConfigWindow::cbReadonly_toggled(bool selected)
{
    ui->cbPosixFormat->setEnabled(!selected);
    ui->cbPosixLink->setEnabled(!selected);
    ui->cbPosixUnlink->setEnabled(!selected);
    ui->cbPosixMkdir->setEnabled(!selected);
    ui->cbPosixRmDir->setEnabled(!selected);
    ui->framePosixRenames->setEnabled(!selected);
    ui->cbPosixFtruncate->setEnabled(!selected);

    ui->cbFseSetMask->setEnabled(!selected);
    ui->cbFseTruncate->setEnabled(!selected);

    ui->cbUpdateAtime->setEnabled(!selected && ui->cbInodeTimestamps->isChecked());

    ui->tabTransactionPts->setEnabled(!selected);
    // Disable tr settings tab
    ui->tabWidget->setTabEnabled(ui->tabWidget->count() - 1, !selected);
}

void ConfigWindow::rbtnUsePosix_toggled(bool selected)
{
    ui->framePosixOps->setVisible(selected);
    ui->frameFseOps->setVisible(!selected);

    ui->cbTransactFileCreate->setEnabled(selected);
    ui->cbTransactDirCreate->setEnabled(selected && ui->cbPosixMkdir->isChecked());
    ui->cbTransactRename->setEnabled(selected && ui->cbPosixRename->isChecked());
    ui->cbTransactLink->setEnabled(selected && ui->cbPosixLink->isChecked());
    ui->cbTransactUnlink->setEnabled(selected && ui->cbPosixUnlink->isChecked());
    ui->cbTransactFSync->setEnabled(selected);
    ui->cbTransactClose->setEnabled(selected);

    ui->cbTransactTruncate->setEnabled(
                selected && ui->cbPosixFtruncate->isChecked()
                || !selected && ui->cbFseTruncate->isChecked());
}

void ConfigWindow::cbPosixRename_toggled(bool selected)
{
    ui->cbPosixAtomicRename->setEnabled(selected);
    ui->cbTransactRename->setEnabled(selected);
}

void ConfigWindow::cbPosixMkdir_toggled(bool selected)
{
    ui->cbTransactDirCreate->setEnabled(selected);
}

void ConfigWindow::cbPosixLink_toggled(bool selected)
{
    ui->cbTransactLink->setEnabled(selected);
}

void ConfigWindow::cbPosixUnlink_toggled(bool selected)
{
    ui->cbTransactUnlink->setEnabled(selected);
}

void ConfigWindow::cbPosixFtruncate_toggled(bool selected)
{
    ui->cbTransactTruncate->setEnabled(selected);
}

void ConfigWindow::cbFseTruncate_toggled(bool selected)
{
    ui->cbTransactTruncate->setEnabled(selected);
}

void ConfigWindow::cbInodeTimestamps_toggled(bool selected)
{
    ui->cbUpdateAtime->setEnabled(selected && !ui->cbReadonly->isChecked());
}

void ConfigWindow::rbtnMemUseCStd_toggled(bool selected)
{
    if(selected)
    {
        ui->frameMemFnsCust->setEnabled(false);
        ui->leMemcpy->setText(cstdMemcpy);
        ui->leMemmov->setText(cstdMemmov);
        ui->leMemset->setText(cstdMemset);
        ui->leMemcmp->setText(cstdMemcmp);
        ui->leStrlen->setText(cstdStrlen);
        ui->leStrcmp->setText(cstdStrcmp);
        ui->leStrncmp->setText(cstdStrncmp);
        ui->leStrncpy->setText(cstdStrncpy);
        ui->leIncludeFile->setText(cstdStringH);
    }
}

void ConfigWindow::rbtnMemUseReliance_toggled(bool selected)
{
    if(selected)
    {
        ui->frameMemFnsCust->setEnabled(false);
        ui->leMemcpy->clear();
        ui->leMemmov->clear();
        ui->leMemset->clear();
        ui->leMemcmp->clear();
        ui->leStrlen->clear();
        ui->leStrcmp->clear();
        ui->leStrncmp->clear();
        ui->leStrncpy->clear();
        ui->leIncludeFile->clear();
    }
}

void ConfigWindow::rbtnMemCustomize_toggled(bool selected)
{
    if(selected)
    {
        ui->frameMemFnsCust->setEnabled(true);
    }
}

void ConfigWindow::cbTransactManual_toggled(bool selected)
{
    ui->frameAutomaticTransactions->setEnabled(!selected);
}