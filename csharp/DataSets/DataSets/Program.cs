using System;
using System.Collections.Generic;
using System.Text;

using System.Data;

namespace DataSets
{
    class Program
    {
        static void Main(string[] args)
        {
            // our dataset..
            DataSet carsInventoryDS = new DataSet("Car Inventory");
            carsInventoryDS.ExtendedProperties["TimeStamp"] = DateTime.Now;
            carsInventoryDS.ExtendedProperties["Company"] = "UEI training";
            
            
            DataColumn carIDColumn = new DataColumn("CarID",typeof(int));
            carIDColumn.Caption = "Car ID";
            carIDColumn.ReadOnly = true;
            carIDColumn.AllowDBNull = false;
            carIDColumn.Unique = true;
            carIDColumn.AutoIncrement = true;
            carIDColumn.AutoIncrementSeed = 0;
            carIDColumn.AutoIncrementStep = 1;
            carIDColumn.ColumnMapping = MappingType.Attribute;
            
            DataColumn carMakeColumn = new DataColumn("Make",typeof(string));
            carMakeColumn.ColumnMapping = MappingType.Attribute;
            
            DataColumn carColorColumn = new DataColumn("Color",typeof(string));
            carColorColumn.ColumnMapping = MappingType.Attribute;
            
            DataColumn carPetNameColumn = new DataColumn("PetName",typeof(string));
            carPetNameColumn.ColumnMapping = MappingType.Attribute;
            carPetNameColumn.Caption = "Pet Name";
            
            DataColumn carLength = new DataColumn("Length",typeof(int));
            carLength.AllowDBNull = false;
            carLength.ColumnMapping = MappingType.Attribute;
            
            DataTable inventoryTable = new DataTable("Inventory");
            inventoryTable.Columns.AddRange(new DataColumn[] {carIDColumn,
                                                              carMakeColumn,
                                                              carColorColumn,
                                                              carPetNameColumn,
                                                              carLength});
            carsInventoryDS.Tables.Add(inventoryTable);                                                              
                                                              
            // populate with some data..
            DataRow rowToAdd1 = inventoryTable.NewRow();
            rowToAdd1["Make"] = "BMW";
            rowToAdd1["Color"] = "Black";
            rowToAdd1["PetName"] = "Hamlet";
            rowToAdd1["Length"] = 4400;
            inventoryTable.Rows.Add(rowToAdd1);
            rowToAdd1 = inventoryTable.NewRow();
            rowToAdd1["Make"] = "BMW";
            rowToAdd1["Color"] = "Blue";
            rowToAdd1["PetName"] = "BluePiglet";
            rowToAdd1["Length"] = 4400;
            inventoryTable.Rows.Add(rowToAdd1);
            
            DataRow rowToAdd2 = inventoryTable.NewRow();
            rowToAdd2["Make"] = "SAAB";
            rowToAdd2["Color"] = "Red";
            rowToAdd2["PetName"] = "Sea Breeze";
            rowToAdd2["Length"] = 4400;
            inventoryTable.Rows.Add(rowToAdd2);
            rowToAdd2 = inventoryTable.NewRow();
            rowToAdd2["Make"] = "SAAB";
            rowToAdd2["Color"] = "Orange";
            rowToAdd2["PetName"] = "Sea Citrus";
            rowToAdd2["Length"] = 5500;
            inventoryTable.Rows.Add(rowToAdd2);
            
            // write em out as xml schema and xml data objects
            carsInventoryDS.WriteXml("cars.xml");
            carsInventoryDS.WriteXmlSchema("carsSchema.xsd");
            
            Console.WriteLine(rowToAdd1.RowState);
            Console.WriteLine(rowToAdd2.RowState);

            Console.WriteLine("Accepting Changes");
            inventoryTable.AcceptChanges();

            Console.WriteLine(rowToAdd1.RowState);
            Console.WriteLine(rowToAdd2.RowState);
            Console.WriteLine();
            
            for(int curCol = 0; curCol < inventoryTable.Columns.Count;curCol++)
            {
                Console.Write(inventoryTable.Columns[curCol].ColumnName.Trim() + "\t");
            }
            Console.WriteLine("\n------------------------------------");
            for(int curRow = 0; curRow < inventoryTable.Rows.Count; curRow++)
            {
                for(int curCol = 0; curCol < inventoryTable.Columns.Count;curCol++)
                {
                    Console.Write(inventoryTable.Rows[curRow][curCol].ToString() + "\t");
                }
                Console.WriteLine();
            }
            
            Console.WriteLine();
            Console.WriteLine();
            
            DataRow[] Makes = inventoryTable.Select("Make='BMW'");
            foreach(DataRow dr in Makes)
            {
                for(int curCol = 0; curCol < inventoryTable.Columns.Count;curCol++)
                {
                    Console.Write(dr[curCol].ToString() + "\t");
                }
                Console.WriteLine();
            }
            
            Console.WriteLine();
            Console.WriteLine();
            
            Makes = inventoryTable.Select("Make='BMW' and Color='Black'");
            foreach(DataRow dr in Makes)
            {
                for(int curCol = 0; curCol < inventoryTable.Columns.Count;curCol++)
                {
                    Console.Write(dr[curCol].ToString() + "\t");
                }
                Console.WriteLine();
            }
            
            Console.WriteLine();
            Console.WriteLine();
                
            Makes = inventoryTable.Select("Make='BMW'");
            foreach(DataRow dr in Makes)
            {
                dr.Delete();
            }            
            inventoryTable.AcceptChanges();
            
            for(int curCol = 0; curCol < inventoryTable.Columns.Count;curCol++)
            {
                Console.Write(inventoryTable.Columns[curCol].ColumnName.Trim() + "\t");
            }
            Console.WriteLine("\n------------------------------------");
            for(int curRow = 0; curRow < inventoryTable.Rows.Count; curRow++)
            {
                for(int curCol = 0; curCol < inventoryTable.Columns.Count;curCol++)
                {
                    Console.Write(inventoryTable.Rows[curRow][curCol].ToString() + "\t");
                }
                Console.WriteLine();
            }
            
            
        }
        
        static void ShowRowState(DataRow dr)
        {
            Console.WriteLine(dr.RowState);
        }
    }
}
