import { Card, CardActions, CardContent, IconButton } from "@mui/material";
import { Container } from "@mui/system";
import { useEffect, useState } from "react";
import { Link, useParams } from "react-router-dom";
import ArrowBackIcon from "@mui/icons-material/ArrowBack";

import { alignProperty } from "@mui/material/styles/cssUtils";
import { BACKEND_URL } from "../../constants";
import { Author } from "../../models/Author";
import { AuthorWithBookDTO } from "../../models/AuthorWithBookDTO";
import EditIcon from "@mui/icons-material/Edit";
import DeleteForeverIcon from "@mui/icons-material/DeleteForever";

export const AuthorDetails = () => {
	const { authorId } = useParams();
	const [author, setAuthor] = useState<AuthorWithBookDTO>();

	useEffect(() => {
		const fetchAuthor = async () => {
			const response = await fetch(`${BACKEND_URL}/authors/${authorId}`);
			const author = await response.json();
			setAuthor(author);
		};
		fetchAuthor();
	}, [authorId]);

	return (
		<Container>
			<Card>
				<CardContent>
					<IconButton component={Link} sx={{ mr: 3 }} to={`/authors`}>
						<ArrowBackIcon />
					</IconButton>{" "}
					<h3>Author Details</h3>
					<p>Name: {author?.name}</p>
                    <p>Year of Birth: {author?.yearOfBirth}</p>
                    <p>Address: {author?.address}</p>
                    <p>Email: {author?.email}</p>
                    <p>Phone Number: {author?.phoneNumber}</p>
                    <p style={{textAlign: "left", marginLeft: "12px"}}>Books:</p>
                    <ul>
						{author?.books?.map((book) => (
                            <li key={book.id}>{book.title}</li>
						))}
					</ul>
				</CardContent>
                <CardActions>
					<IconButton component={Link} sx={{ mr: 3 }} to={`/authors/${authorId}/edit`}>
						<EditIcon />
					</IconButton>

					<IconButton component={Link} sx={{ mr: 3 }} to={`/authors/${authorId}/delete`}>
						<DeleteForeverIcon sx={{ color: "red" }} />
					</IconButton>
				</CardActions>

			</Card>
		</Container>
	);
};