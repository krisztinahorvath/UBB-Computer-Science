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

namespace DBMSLab1
{
    public partial class Form1 : Form
    {

        private SqlConnection dbConnection;
        private SqlDataAdapter daTeas, daTeaTypes;
        private DataSet tableData;
        private DataRelation drTeaTypeTeas;
        BindingSource bsTeas, bsTeaTypes;

        public Form1()
        {
            InitializeComponent();
        }


        private void ReloadTeasTableView()
        {
            if (tableData.Tables["Teas"] != null)
            {
                tableData.Tables["Teas"].Clear();
            }
            daTeas.Fill(tableData, "Teas");
            DataGridViewTeas.DataSource = bsTeas;
        }

        private void DataGridViewTeaTypes_SelectionChanged(object sender, EventArgs e)
        {
            textBoxTeaId.Clear();
            textBoxTeaTypeId.Clear();
            textBoxName.Clear();
            textBoxQuantity.Clear();
            textBoxPrice.Clear();
            textBoxDistributorId.Clear();

            if (DataGridViewTeaTypes.SelectedRows.Count != 0)
            {
                DataGridViewRow selectedRow = DataGridViewTeaTypes.SelectedRows[0];
                daTeas.SelectCommand = new SqlCommand("SELECT * FROM Teas WHERE ttid = " + selectedRow.Cells[0].Value, dbConnection);

                ReloadTeasTableView();
            }
        }

        private void DataGridViewTeas_SelectionChanged(object sender, EventArgs e)
        {
            if (DataGridViewTeas.SelectedRows.Count != 0)
            {
                DataGridViewRow selectedRow = DataGridViewTeas.SelectedRows[0];

                textBoxTeaId.Text = selectedRow.Cells[0].Value.ToString();
                textBoxTeaTypeId.Text = selectedRow.Cells[1].Value.ToString();
                textBoxName.Text = selectedRow.Cells[2].Value.ToString();
                textBoxQuantity.Text = selectedRow.Cells[3].Value.ToString();
                textBoxPrice.Text = selectedRow.Cells[4].Value.ToString();
                textBoxDistributorId.Text = selectedRow.Cells[5].Value.ToString();

            }
        }

        private void Form1_Load_1(object sender, EventArgs e)
        {
            dbConnection = new SqlConnection("Server=DESKTOP-1AIPMIG\\SQLEXPRESS;Database=TeaShop;Trusted_Connection=True");
            dbConnection.Open();

            /// TeaTypes
            daTeaTypes = new SqlDataAdapter("SELECT * FROM TeaTypes", dbConnection);
            tableData = new DataSet();
            daTeaTypes.Fill(tableData, "TeaTypes");
            DataGridViewTeaTypes.SelectionMode = DataGridViewSelectionMode.FullRowSelect;


            /// Teas
            daTeas = new SqlDataAdapter("SELECT * FROM Teas", dbConnection);
            daTeas.Fill(tableData, "Teas");
            DataGridViewTeas.SelectionMode = DataGridViewSelectionMode.FullRowSelect;

            DataColumn teaTypeIdTeaType = tableData.Tables["TeaTypes"].Columns["ttid"];
            DataColumn teaTypeIdTea = tableData.Tables["Teas"].Columns["ttid"];
            drTeaTypeTeas = new DataRelation("FK_TeaType_Tea", teaTypeIdTeaType, teaTypeIdTea);
            tableData.Relations.Add(drTeaTypeTeas);

            bsTeaTypes = new BindingSource();
            bsTeaTypes.DataSource = tableData;
            bsTeaTypes.DataMember = "TeaTypes";

            bsTeas = new BindingSource();
            bsTeas.DataSource = bsTeaTypes;
            bsTeas.DataMember = "FK_TeaType_Tea";
            DataGridViewTeaTypes.DataSource = bsTeaTypes;
        }

        private void buttonAdd_Click(object sender, EventArgs e)
        {
            SqlCommand command = new SqlCommand("INSERT INTO Teas (ttid, name, quantity, price, did)" +
                "VALUES (@ttid, @name, @quantity, @price, @did)", dbConnection);

            if (textBoxTeaId.Text.Length != 0)
            {
                MessageBox.Show("The TeaId field should be empty!");
            }
            else
            {
                try
                {
                    if (textBoxTeaTypeId.Text.Length != 0)
                    {
                        int ttid = 0 ;

                        try
                        {
                            ttid = Int32.Parse(textBoxTeaTypeId.Text);
                        }
                        catch(Exception ex) { MessageBox.Show("The TeaTypeId field should be an integer!"); }
                        

                        int quantity;
                        if (textBoxQuantity.Text.Length != 0)
                            quantity = Int32.Parse(textBoxQuantity.Text);
                        else
                        {
                            MessageBox.Show("Please provide a Quantity!");
                            return;
                        }

                        float convertPrice;
                        decimal price;
                        if (textBoxPrice.Text.Length != 0)
                        {
                            convertPrice = float.Parse(textBoxPrice.Text);
                            price = Math.Round((decimal)convertPrice, 2);
                        }
                        else price = 1;


                        int did;
                        if (textBoxDistributorId.Text.Length != 0)
                            did = Int32.Parse(textBoxDistributorId.Text);
                        else
                        {
                            MessageBox.Show("Please provide a DistributorId!");
                            return;
                        }


                        if (textBoxName.Text.Length == 0)
                        {
                            MessageBox.Show("Please provide a Name!");
                            return;
                        }

                        /// ttid
                        command.Parameters.Add("@ttid", SqlDbType.Int);
                        command.Parameters["@ttid"].Value = ttid;

                        /// name 
                        command.Parameters.Add("@name", SqlDbType.VarChar, 40);
                        command.Parameters["@name"].Value = textBoxName.Text;

                        /// quantity
                        command.Parameters.Add("@quantity", SqlDbType.Int);
                        command.Parameters["@quantity"].Value = quantity;

                        /// price
                        command.Parameters.Add("@price", SqlDbType.Float);
                        command.Parameters["@price"].Value = price;

                        /// did
                        command.Parameters.Add("@did", SqlDbType.Int);
                        command.Parameters["@did"].Value = did;

                        try
                        {
                            daTeas.InsertCommand = command;
                            daTeas.InsertCommand.ExecuteNonQuery();

                            ReloadTeasTableView();

                            MessageBox.Show("Add executed successfully!");
                        }
                        catch (SqlException ex)
                        {
                            MessageBox.Show(ex.Message);
                        }

                        
                    }
                    else
                        MessageBox.Show("Please provide a TeaTypeId!");
                }
                catch (SqlException ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }
        }

        private void buttonRemove_Click(object sender, EventArgs e)
        {
            SqlCommand command = new SqlCommand("DELETE FROM Teas where tid = @tid", dbConnection);

            if (textBoxTeaId.Text.Length == 0)
            {
                MessageBox.Show("Please provide a TeaId!");
            }
            else
            {
                try
                {
                    int tid = Int32.Parse(textBoxTeaId.Text);

                    command.Parameters.Add("@tid", SqlDbType.Int);
                    command.Parameters["@tid"].Value = tid;
                }
                catch(Exception ex) { MessageBox.Show("The TeaId should be an integer!"); }
                

                try
                {
                    daTeas.DeleteCommand = command;
                    int nrOfDeletedTeas = daTeas.DeleteCommand.ExecuteNonQuery();
                    if (nrOfDeletedTeas == 0)
                        MessageBox.Show("There is no Tea with the given id!");
                    else
                    {
                        ReloadTeasTableView();
                        MessageBox.Show("Remove executed successfully!");
                    }
                        

                }
                catch (SqlException ex)
                {
                    MessageBox.Show(ex.Message);
                }


            }
        }

        private void buttonUpdate_Click(object sender, EventArgs e)
        {

            SqlCommand command = new SqlCommand("UPDATE Teas SET ttid = @ttid, name = @name, " +
                "quantity = @quantity, price = @price, did = @did " +
                "WHERE tid = @tid", dbConnection);

            try
            {
                if(textBoxTeaId.Text.Length == 0)
                {
                    MessageBox.Show("Please provide a TeaId!");
                    return;
                }

                if (textBoxTeaTypeId.Text.Length != 0)
                {
                    int ttid = Int32.Parse(textBoxTeaTypeId.Text);

                    int tid = Int32.Parse(textBoxTeaId.Text);

                    int quantity;
                    if (textBoxQuantity.Text.Length != 0)
                        quantity = Int32.Parse(textBoxQuantity.Text);
                    else
                    {
                        MessageBox.Show("Please provide a Quantity!");
                        return;
                    }

                    float convertPrice;
                    decimal price;
                    if (textBoxPrice.Text.Length != 0)
                    {
                        convertPrice = float.Parse(textBoxPrice.Text);
                        price = Math.Round((decimal)convertPrice, 2);
                    }
                    else price = 1;


                    int did;
                    if (textBoxDistributorId.Text.Length != 0)
                        did = Int32.Parse(textBoxDistributorId.Text);
                    else
                    {
                        MessageBox.Show("Please provide a DistributorId!");
                        return;
                    }


                    if (textBoxName.Text.Length == 0)
                    {
                        MessageBox.Show("Please provide a Name!");
                        return;
                    }


                    /// tid
                    command.Parameters.Add("@tid", SqlDbType.Int);
                    command.Parameters["@tid"].Value = tid;

                    /// ttid
                    command.Parameters.Add("@ttid", SqlDbType.Int);
                    command.Parameters["@ttid"].Value = ttid;

                    /// name 
                    command.Parameters.Add("@name", SqlDbType.VarChar, 40);
                    command.Parameters["@name"].Value = textBoxName.Text;

                    /// quantity
                    command.Parameters.Add("@quantity", SqlDbType.Int);
                    command.Parameters["@quantity"].Value = quantity;

                    /// price
                    command.Parameters.Add("@price", SqlDbType.Float);
                    command.Parameters["@price"].Value = price;

                    /// did
                    command.Parameters.Add("@did", SqlDbType.Int);
                    command.Parameters["@did"].Value = did;

                    try
                    {
                        daTeas.UpdateCommand = command;
                        int nrOfUpdatedTeas = daTeas.UpdateCommand.ExecuteNonQuery();

                        if (nrOfUpdatedTeas == 0)
                        {
                            MessageBox.Show("There is no Tea with the given id!");
                        }
                        else
                        {
                            ReloadTeasTableView();
                            MessageBox.Show("Update executed successfully!");
                        }

                    }
                    catch (SqlException ex)
                    {
                        MessageBox.Show(ex.Message);
                    }

                }
                else
                {
                    MessageBox.Show("Please provide a TeaTypeId!");
                }
            }
            catch (SqlException ex)
            {
                MessageBox.Show(ex.Message);
            }

            //SqlCommandBuilder builder = new SqlCommandBuilder(daTeas);
            //daTeas.UpdateCommand = builder.GetUpdateCommand();

            //try
            //{
            //    daTeas.Update(tableData, "Teas");
            //    ReloadTeasTableView();
            //    MessageBox.Show("Update executed successfully!");
            //}
            //catch(SqlException ex)
            //{
            //    if (ex.Number == 547)
            //        MessageBox.Show("The TeaTypeId or the DistributorId is invalid!");
            //    else
            //        MessageBox.Show(ex.Message);
            //}
            
        }
    }
}