using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient;
using System.Globalization;
using System.Runtime.InteropServices;
using System.Configuration;

namespace DBMSLab1
{
    public partial class Form1 : Form
    {

        private SqlConnection dbConnection;
        private SqlDataAdapter daChild, daParent;
        private DataSet tableData;
        private DataRelation drParentChild;
        BindingSource bsChild, bsParent;

        string getConnectionString = "<Connection string>";
        string getDatabase = ConfigurationManager.AppSettings["Database"].ToString();
        string getParentTableName = ConfigurationManager.AppSettings["ParentTableName"].ToString();
        string getChildTableName = ConfigurationManager.AppSettings["ChildTableName"].ToString();
        string getParentSelectQuery = ConfigurationManager.AppSettings["ParentSelectQuery"].ToString();
        string getChildSelectQuery = ConfigurationManager.AppSettings["ChildSelectQuery"].ToString();
        string getParentReferencedKey = ConfigurationManager.AppSettings["ParentReferencedKey"].ToString();
        string getChildForeignKey = ConfigurationManager.AppSettings["ChildForeignKey"].ToString();
        string getParentSelectionQuery = ConfigurationManager.AppSettings["ParentSelectionQuery"].ToString();

        public Form1()
        {
            InitializeComponent();
        }

        private void DataGridViewChild_DataError(object sender, DataGridViewDataErrorEventArgs e)
        {
            if (e.Exception is InvalidConstraintException)
                MessageBox.Show("The parent id doesn't exist!");
            else if (e.Exception is FormatException)
                MessageBox.Show(e.Exception.Message);
            else
                try
                {
                    throw e.Exception;
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.ToString());
                }
        }

        private void ReloadChildTableView()
        {
            if (tableData.Tables[getChildTableName] != null)
            {
                tableData.Tables[getChildTableName].Clear();
            }
            daChild.Fill(tableData, getChildTableName); 
            DataGridViewChild.DataSource = bsChild;
        }

        private void DataGridViewParent_SelectionChanged(object sender, EventArgs e)
        {
            if (DataGridViewParent.SelectedRows.Count != 0)
            {
                DataGridViewRow selectedRow = DataGridViewParent.SelectedRows[0];
                string selectCommandString = String.Format(getParentSelectionQuery, selectedRow.Cells[0].Value);
                daChild.SelectCommand = new SqlCommand(selectCommandString, dbConnection);
                ReloadChildTableView();
            }

        }


        private void Form1_Load_1(object sender, EventArgs e)
        {
            dbConnection = new SqlConnection(getConnectionString);
            dbConnection.Open();

            tableData = new DataSet();

            daParent = new SqlDataAdapter(getParentSelectQuery, dbConnection);
            daParent.Fill(tableData, getParentTableName);
            DataGridViewParent.SelectionMode = DataGridViewSelectionMode.FullRowSelect;

            daChild = new SqlDataAdapter(getChildSelectQuery, dbConnection);
            daChild.Fill(tableData, getChildTableName);
            DataGridViewChild.SelectionMode = DataGridViewSelectionMode.FullRowSelect;

            DataColumn referenceId = tableData.Tables[getParentTableName].Columns[getParentReferencedKey];
            DataColumn foreignId = tableData.Tables[getChildTableName].Columns[getChildForeignKey];
            drParentChild = new DataRelation("FK_Parent_Child", referenceId, foreignId);
            tableData.Relations.Add(drParentChild);

            bsParent = new BindingSource();
            bsParent.DataSource = tableData;
            bsParent.DataMember = getParentTableName;

            bsChild = new BindingSource();
            bsChild.DataSource = bsParent;
            bsChild.DataMember = "FK_Parent_Child";

            DataGridViewParent.DataSource = bsParent;
        }


        private void button1_Click(object sender, EventArgs e)
        {
            SqlCommandBuilder builder = new SqlCommandBuilder(daChild);
            daChild.UpdateCommand = builder.GetUpdateCommand();
            daChild.InsertCommand = builder.GetInsertCommand();
            daChild.DeleteCommand = builder.GetDeleteCommand();
            try
            {
                daChild.Update(tableData, getChildTableName);
                MessageBox.Show("The database was updated successfully!!");
            }
            catch (SqlException sqlException)
            {
                MessageBox.Show(sqlException.Message);
            }
            ReloadChildTableView();
        }
    }
}