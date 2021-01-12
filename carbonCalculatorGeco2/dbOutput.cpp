#include "dbOutput.h"
#include "inputOutput.h"

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <iostream>


bool createOutputDB(QSqlDatabase &dbOutput, QString dbName)
{
    dbOutput = QSqlDatabase::addDatabase("QSQLITE", "output");
    dbOutput.setDatabaseName(dbName);

    if (! dbOutput.open())
    {
        std::cout << "Error opening output db:" << dbOutput.lastError().text().toStdString() << std::endl;
        return false;
    }

    if (! createTableGeneral(dbOutput))
        return false;
    if (! createTableClimate(dbOutput))
        return false;
    if (! createTableSoil(dbOutput))
        return false;
    if (! createTableCropField(dbOutput))
        return false;
    // TODO other tables

    return true;
}

bool saveOutput(QString id, QSqlDatabase &dbOutput, TinputData &inputData)
{
    if (! saveTableGeneral(id, dbOutput, inputData, "general"))
        return false;
    if (! saveTableClimate(dbOutput, inputData, "climate"))
        return false;
    if (! saveTableSoil(dbOutput, inputData, "soil"))
        return false;
    //if (! saveTableCropField(dbOutput, inputData, "crop_field"))
        return false;


    // TODO save other tables

    return true;
}


bool createTableGeneral(QSqlDatabase &dbOutput)
{
    QString queryString = "DROP TABLE general";
    QSqlQuery myQuery = dbOutput.exec(queryString);

    queryString = "CREATE TABLE general "
                  " (id TEXT, enterprise_name TEXT, nr_field INTEGER, year INTEGER, "
                  " country TEXT, latitude REAL, longitude REAL, "
                  " field_size REAL, field_slope REAL )";

    myQuery = dbOutput.exec(queryString);

    if (myQuery.lastError().isValid())
    {
        std::cout << "Error in creating table 'general': " << myQuery.lastError().text().toStdString();
        return false;
    }

    return true;
}


bool saveTableGeneral(QString id, QSqlDatabase &dbOutput, TinputData &inputData, QString tableName)
{
    QString queryOutput = "INSERT INTO " + tableName
                       + " (id, enterprise_name, nr_field, year, country, latitude, longitude, field_size, field_slope) "
                       " VALUES ";

    queryOutput += "('" + id + "'"
                 + ",'" + inputData.general.enterpriseName + "'"
                 + "," + QString::number(inputData.general.nrField)
                 + "," + QString::number(inputData.general.year)
                 + ",'" + inputData.general.idCountry + "'"
                 + "," + QString::number(inputData.general.latitude, 'g', 3)
                 + "," + QString::number(inputData.general.longitude, 'g', 3)
                 + "," + QString::number(inputData.general.fieldSize, 'g', 3)
                 + "," + QString::number(inputData.general.fieldSlope, 'g', 3)
                 + ")";

    QSqlQuery myQuery = dbOutput.exec(queryOutput);
    if (myQuery.lastError().isValid())
    {
        std::cout << "Error in saving table " + tableName.toStdString() + ": " << myQuery.lastError().text().toStdString();
        return false;
    }

    return true;
}

bool createTableClimate(QSqlDatabase &dbOutput)
{
    QString queryString = "DROP TABLE climate";
    QSqlQuery myQuery = dbOutput.exec(queryString);

    queryString = "CREATE TABLE climate "
                  " (annual_mean_temperature REAL, cumulated_annual_precipitation REAL, "
                  " reference_evapotranspiration REAL, climatic_water_balance REAL )";


    myQuery = dbOutput.exec(queryString);

    if (myQuery.lastError().isValid())
    {
        std::cout << "Error in creating table 'climate': " << myQuery.lastError().text().toStdString();
        return false;
    }

    return true;
}


bool saveTableClimate(QSqlDatabase &dbOutput, TinputData &inputData, QString tableName)
{
    QString queryOutput = "INSERT INTO " + tableName
                       + " (annual_mean_temperature, cumulated_annual_precipitation, "
                         " reference_evapotranspiration , climatic_water_balance)"
                       " VALUES ";

    queryOutput += "(" + QString::number(inputData.climate.meanTemperature)
                 + "," + QString::number(inputData.climate.annualRainfall)
                 + "," + QString::number(inputData.climate.referenceEvapotranspiration,'g', 3)
                 + "," + QString::number(inputData.climate.climaticWaterBalance,'g', 3)
                 + ")";

    QSqlQuery myQuery = dbOutput.exec(queryOutput);
    if (myQuery.lastError().isValid())
    {
        std::cout << "Error in saving table " + tableName.toStdString() + ": " << myQuery.lastError().text().toStdString();
        return false;
    }

    return true;
}

bool createTableSoil(QSqlDatabase &dbOutput)
{
    QString queryString = "DROP TABLE soil";
    QSqlQuery myQuery = dbOutput.exec(queryString);

    queryString = "CREATE TABLE soil "
                  " (soil_depth REAL, drainage TEXT, pH REAL, texture TEXT, "
                  " organic_matter REAL, skeleton REAL, available_water_capacity REAL, "
                  " total_nitrogen REAL, C_N_ratio REAL )";

    myQuery = dbOutput.exec(queryString);

    if (myQuery.lastError().isValid())
    {
        std::cout << "Error in creating table 'soil': " << myQuery.lastError().text().toStdString();
        return false;
    }

    return true;
}


bool saveTableSoil(QSqlDatabase &dbOutput, TinputData &inputData, QString tableName)
{
    QString queryOutput = "INSERT INTO " + tableName
                       + " (soil_depth, drainage, pH, texture, "
                         " organic_matter, skeleton, available_water_capacity, "
                         " total_nitrogen, C_N_ratio) "
                       " VALUES ";

    queryOutput += "(" + QString::number(inputData.soil.depth, 'g', 1)
                 + ",'" + inputData.soil.drainage + "'"
                 + "," + QString::number(inputData.soil.pH, 'g', 1)
                 + ",'" + inputData.soil.texture + "'"
                 + "," + QString::number(inputData.soil.organicMatter, 'g', 1)
                 + "," + QString::number(inputData.soil.skeleton, 'g', 1)
                 + "," + QString::number(inputData.soil.availableWaterCapacity, 'g', 1)
                 + "," + QString::number(inputData.soil.totalNitrogen, 'g', 1)
                 + "," + QString::number(inputData.soil.carbonNitrogenRatio, 'g', 1)
                 + ")";

    QSqlQuery myQuery = dbOutput.exec(queryOutput);
    if (myQuery.lastError().isValid())
    {
        std::cout << "Error in saving table " + tableName.toStdString() + ": " << myQuery.lastError().text().toStdString();
        return false;
    }

    return true;
}

bool createTableCropField(QSqlDatabase &dbOutput)
{
    QString queryString = "DROP TABLE crop_field";
    QSqlQuery myQuery = dbOutput.exec(queryString);

    queryString = "CREATE TABLE crop_field "
                  " (crop_type TEXT, density INTEGER, delta_trees INTEGER,"
                  "orchard_age INTEGER, DBH REAL, "
                  " tree_height REAL, organic_management TEXT, yield REAL, "
                  " no_tillage_area REAL, minimum_tillage_area REAL,"
                  "cover_crop_area REAL, forestry_area REAL, sparse_vegetation_area REAL,"
                  "woody_residue_weight_1 REAL,woody_residue_weight_2 REAL,"
                  "woody_residue_treatment_1 TEXT,woody_residue_treatment_2 TEXT,"
                  "green_residue_weight_1 REAL,green_residue_weight_2 REAL,"
                  "green_residue_treatment_1 TEXT,green_residue_treatment_2 TEXT"
                  ")";

    myQuery = dbOutput.exec(queryString);

    if (myQuery.lastError().isValid())
    {
        std::cout << "Error in creating table 'soil': " << myQuery.lastError().text().toStdString();
        return false;
    }

    return true;
}


bool saveTableCropField(QSqlDatabase &dbOutput, TinputData &inputData, QString tableName)
{
    QString queryOutput = "INSERT INTO " + tableName
                       + " (crop_type, density,delta_trees, orchard_age, DBH, "
                         " tree_height, organic_management, yield, "
                         " no_tillage_area, minimum_tillage_area"
                         "cover_crop_area, forestry_area, sparse_vegetation_area"
                         "woody_residue_weight_1,woody_residue_weight_2"
                         "woody_residue_treatment_1,woody_residue_treatment_2"
                         "green_residue_weight_1,green_residue_weight_2"
                         "green_residue_treatment_1,green_residue_treatment_2) "
                       " VALUES ";

    queryOutput += "('" + inputData.cropFieldManagement.cropName + "'"
                + QString::number(inputData.cropFieldManagement.treeDensity)
                + QString::number(inputData.cropFieldManagement.deadTreeDensity)
                + QString::number(inputData.cropFieldManagement.orchardAge)
                + QString::number(inputData.cropFieldManagement.treeDBH)
                + QString::number(inputData.cropFieldManagement.treeHeight)
                + ",'" + inputData.cropFieldManagement.isOrganic + "'"
                + "," + QString::number(inputData.cropFieldManagement.yield, 'g', 1)
                + "," + QString::number(inputData.cropFieldManagement.noTillage, 'g', 1)
                + "," + QString::number(inputData.cropFieldManagement.minTillage, 'g', 1)
                + "," + QString::number(inputData.cropFieldManagement.coverCrop, 'g', 1)
                + "," + QString::number(inputData.cropFieldManagement.forest, 'g', 1)
                + "," + QString::number(inputData.cropFieldManagement.sparseVegetation, 'g', 1)
                + "," + QString::number(inputData.cropFieldManagement.woodyResidueWeight[0], 'g', 1)
                + "," + QString::number(inputData.cropFieldManagement.woodyResidueWeight[1], 'g', 1)
                + ",'" + inputData.cropFieldManagement.woodyResidueTreatment[0] + "'"
                + ",'" + inputData.cropFieldManagement.woodyResidueTreatment[1] + "'"
                + "," + QString::number(inputData.cropFieldManagement.greenResidueWeight[0], 'g', 1)
                + "," + QString::number(inputData.cropFieldManagement.greenResidueWeight[1], 'g', 1)
                + ",'" + inputData.cropFieldManagement.greenResidueTreatment[0] + "'"
                + ",'" + inputData.cropFieldManagement.greenResidueTreatment[1]
                + "')";

    QSqlQuery myQuery = dbOutput.exec(queryOutput);
    if (myQuery.lastError().isValid())
    {
        std::cout << "Error in saving table " + tableName.toStdString() + ": " << myQuery.lastError().text().toStdString();
        return false;
    }

    return true;
}
