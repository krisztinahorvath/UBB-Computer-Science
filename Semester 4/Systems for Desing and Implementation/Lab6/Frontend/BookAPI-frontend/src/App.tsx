import { useState } from "react";
import CssBaseline from "@mui/material/CssBaseline";
import Box from "@mui/material/Box";
import Container from "@mui/material/Container";
import * as React from "react";
import { AppBar, Toolbar, IconButton, Typography, Button } from "@mui/material";
import MenuIcon from "@mui/icons-material/Menu";
import { BrowserRouter as Router, Routes, Route } from "react-router-dom";
import { AppMenu } from "./components/AppMenu";
import { HomePage } from "./components/HomePage";
import { ShowAllAuthors } from "./components/authors/ShowAllAuthors";
import { AuthorDetails } from "./components/authors/AuthorDetails";
import { AddAuthor } from "./components/authors/AddAuthor";
import { DeleteAuthor } from "./components/authors/DeleteAuthor";
import { UpdateAuthor } from "./components/authors/UpdateAuthor";
import { AuthorWithAvgBookLength } from "./components/authors/AuthorsStatisticalReport";
import { SortAuthors } from "./components/authors/SortAuthors";

function App() {

  return (
		<React.Fragment>
			<Router>
				<AppMenu />

				<Routes>
					<Route path="/" element={<HomePage />} />
					<Route path="/authors" element={<ShowAllAuthors />} />
					<Route path="/authors/add" element={<AddAuthor />} /> 
					<Route path="/authors/:authorId/details" element={<AuthorDetails />} />
					<Route path="/authors/:authorId/delete" element={<DeleteAuthor />} />
					<Route path="/authors/:authorId/edit" element={<UpdateAuthor />} />
					<Route path="/authors/order-by-page-number" element={<AuthorWithAvgBookLength />} />	
					<Route path="/authors/ordered-authors" element={< SortAuthors/>} />	
				</Routes>
			</Router>
		</React.Fragment>
	);
}

export default App
