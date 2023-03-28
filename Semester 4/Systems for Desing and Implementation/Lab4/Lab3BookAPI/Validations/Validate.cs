using Lab3BookAPI.Model;
using System.Text.RegularExpressions;

namespace Lab3BookAPI.Validations
{
    public class Validate
    {
        public Validate() { }
      
        public bool IsEmailUnique(in BookContext _context, string email)
        {
            return !_context.Authors.Any(a => a.Email == email);

        }

        public bool IsDateValid(int year)
        {
            return year > 1500 && year <= DateTime.Now.Year;
        }

        public bool IsStringNonEmpty(string value)
        {
            if (value == null)
            {
                return false;
            }

            return value.Length != 0;
        }

        public bool IsPositive(int value) 
        { 
            if(value > 0)
                return true;
            return false;
        }

        public bool IsValidEmail(string email)
        {
            try
            {
                var addr = new System.Net.Mail.MailAddress(email);
                return addr.Address == email;
            }
            catch
            {
                return false;
            }
        }

    }
}
