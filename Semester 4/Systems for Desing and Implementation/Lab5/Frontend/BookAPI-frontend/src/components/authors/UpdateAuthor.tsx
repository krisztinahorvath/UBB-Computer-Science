import { Button, Card, CardActions, CardContent, Container, FormLabel, IconButton, TextField, colors } from "@mui/material";
import axios from "axios";
import { Link, useNavigate, useParams } from "react-router-dom";

import ArrowBackIcon from "@mui/icons-material/ArrowBack";

import { useEffect, useState } from "react";
import { BACKEND_URL } from "../../constants";
import { Author } from "../../models/Author";


export const UpdateAuthor = () => {
    const { authorId } = useParams<{ authorId: string }>();
    const navigate = useNavigate();
    const [loading, setLoading] = useState(false);

    const [author, setAuthor] = useState<Author>({
        id: parseInt(String(authorId)),
        name: "",
        yearOfBirth: 0,
        address: "",
        email: "",
        phoneNumber: "",
        bookAuthors: []
    });

    useEffect(() => {
        setLoading(true);
        fetch(`${BACKEND_URL}/authors/${authorId}/`).then(response => response.json()).then(data => {
          setAuthor(data);
          setLoading(false);
        });
      }, [authorId]);

    const updateAuthor = async (event: { preventDefault: () => void }) => {
        event.preventDefault();
        setLoading(true);
        fetch(`${BACKEND_URL}/authors/${authorId}/`, {
            method: 'PUT',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify(author)
        }).then(response => {
            if (response.ok) {
                alert("Author updated successfully");
            } else {
                console.error('Error updating author:', response.statusText);
            }
            navigate(`/authors/`);
            setLoading(false);
        }).catch(error => {
            console.error('Error updating author:', error);
            setLoading(false);
        });
    }

    const handleCancel = (event: { preventDefault: () => void }) => {
		event.preventDefault();
		navigate("/authors");
	};

    return (
        <Container>
            <Card>
				<CardContent>
                    <IconButton component={Link} sx={{ mr: 3 }} to={`/authors`}>
						<ArrowBackIcon />
					</IconButton>{" "}
                    <form onSubmit={updateAuthor} style={{display: "flex", flexDirection: "column", padding: "8px"}}>
                        <Container sx={{padding: "3px"}} style={{display: "flex", flexDirection: "row", justifyContent: "space-around"}}>
                            <FormLabel style={{marginTop: "15px", fontSize: "18px"}}>
                                Name
                            </FormLabel>
                            <TextField
                                id="name"
                                variant="outlined"
                                onChange={(event) => setAuthor({ ...author, name: event.target.value })}
                            />
                        </Container>
    
                        <Container sx={{padding: "3px"}} style={{display: "flex", flexDirection: "row", justifyContent: "space-around"}}>
                            <FormLabel style={{marginTop: "15px", fontSize: "18px"}}>
                                Year of Birth
                            </FormLabel>
                            <TextField
                                id="yearOfBirth"
                                variant="outlined" 
                                onChange={(event) => setAuthor({ ...author, yearOfBirth: parseInt(event.target.value) })}
                            />
                        </Container>

                        <Container sx={{padding: "3px"}} style={{display: "flex", flexDirection: "row", justifyContent: "space-around"}}>
                            <FormLabel style={{marginTop: "15px", fontSize: "18px"}}>
                                Address
                            </FormLabel>
                            <TextField
                                id="address"
                                variant="outlined"
                                onChange={(event) => setAuthor({ ...author, address: event.target.value })}
                            />
                        </Container>

                        <Container sx={{padding: "3px"}} style={{display: "flex", flexDirection: "row", justifyContent: "space-around"}}>
                            <FormLabel style={{marginTop: "15px", fontSize: "18px"}}>
                                Email
                            </FormLabel>
                            <TextField
                                id="email"
                                variant="outlined"
                                onChange={(event) => setAuthor({ ...author, email: event.target.value })}
                            />
                        </Container>
                        
                        <Container sx={{padding: "3px"}} style={{display: "flex", flexDirection: "row", justifyContent: "space-around"}}>
                            <FormLabel style={{marginTop: "15px", fontSize: "18px"}}>
                                Phone Number
                            </FormLabel>
                            <TextField
                                id="phoneNumber"
                                variant="outlined"
                                onChange={(event) => setAuthor({ ...author, phoneNumber: event.target.value })}
                            />
                        </Container>
                    </form>
				</CardContent>
				<CardActions sx={{ justifyContent: "center" }}>
					<Button type="submit" onClick={updateAuthor} variant="contained">Update</Button>
					<Button onClick={handleCancel} variant="contained">Cancel</Button>
				</CardActions>
			</Card>
        </Container>
    );
}