using Lab10.Models;
using Microsoft.AspNetCore.Http.HttpResults;
using Microsoft.Identity.Client;
using System.Security.Claims;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;


namespace Lab10.Controllers
{
    public class MiddlewareUserAuthentication
    {
        private readonly RequestDelegate _next;

        public MiddlewareUserAuthentication(RequestDelegate next)
        {
            _next = next;
        }

        public async Task Invoke(HttpContext httpContext)
        {
            

            if (httpContext.User.Identity.IsAuthenticated)
            {
                if (!int.TryParse(httpContext.User.FindFirst(ClaimTypes.NameIdentifier)?.Value, out int userId))
                {
                    throw new InvalidOperationException("Invalid token.");
                }
            }
            if (httpContext.Request.Path.Value.Contains("/api/documents") || httpContext.Request.Path.Value.Contains("/api/users/login"))
            {
               
                await _next(httpContext).ConfigureAwait(false);
            }
            else
            {
                throw new InvalidOperationException("Method not allowed!");
            }
           
        }
    }
}
