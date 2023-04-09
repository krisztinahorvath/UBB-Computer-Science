import { Link, useNavigate } from "react-router-dom";
import { useState } from "react";
import axios from "axios";
import { Button, Card, CardActions, CardContent, Container, IconButton, TextField, FormLabel, colors } from "@mui/material";
import ArrowBackIcon from "@mui/icons-material/ArrowBack";
import { useForm } from "react-hook-form";
import { Author } from "../../models/Author";
import { BACKEND_URL } from "../../constants";


export const AddAuthor = () => {
    const navigate = useNavigate();
    const [submitting, setSubmitting] = useState(false);
    const { register, handleSubmit } = useForm<Author>();


    const addAuthor = async (data: Author) => {
        setSubmitting(true);
        try {
            const response = await fetch(`${BACKEND_URL}/authors/`, {
            method: "POST",
            headers: {
              "Content-Type": "application/json",
            },
            body: JSON.stringify(data),
            });
            if (response.ok)
                alert("Author added successfully!");
            else 
                alert("Failed to add author!");
            navigate("/authors");
        } catch (error) {
            console.error(error);
            alert("Failed to add author!");
        }
        setSubmitting(false);
    };

    return (
        <Container>
            <Card>
                <CardContent>
                    <IconButton component={Link} sx={{ mr: 3 }} to={`/authors`}>
						<ArrowBackIcon />
					</IconButton>{" "}
                    <form onSubmit={handleSubmit(addAuthor)} style={{display: "flex", flexDirection: "column", padding: "8px"}}>
                        <Container sx={{padding: "3px"}} style={{display: "flex", flexDirection: "row", justifyContent: "space-around"}}>
                            <FormLabel style={{marginTop: "15px", fontSize: "18px"}}>
                                Name
                            </FormLabel>
                            <TextField {...register("name")}>
                                id="name"
                                label="Author name"
                                variant="outlined"
                            </TextField>
                        </Container>
    
                        <Container sx={{padding: "3px"}} style={{display: "flex", flexDirection: "row", justifyContent: "space-around"}}>
                            <FormLabel style={{marginTop: "15px", fontSize: "18px"}}>
                                Year of Birth
                            </FormLabel>
                            <TextField {...register("yearOfBirth")}>
                                id="yearOfBirth"
                                label="Year of Birth"
                                variant="outlined"
                            </TextField>
                        </Container>

                        <Container sx={{padding: "3px"}} style={{display: "flex", flexDirection: "row", justifyContent: "space-around"}}>
                            <FormLabel style={{marginTop: "15px", fontSize: "18px"}}>
                                Address
                            </FormLabel>
                            <TextField {...register("address")}>
                                id="address"
                                label="Address"
                                variant="outlined"
                            </TextField>
                        </Container>

                        <Container sx={{padding: "3px"}} style={{display: "flex", flexDirection: "row", justifyContent: "space-around"}}>
                            <FormLabel style={{marginTop: "15px", fontSize: "18px"}}>
                                Email
                            </FormLabel>
                            <TextField {...register("email")}>
                                id="email"
                                label="Email"
                                variant="outlined"
                            </TextField>
                        </Container>
                        
                        <Container sx={{padding: "3px"}} style={{display: "flex", flexDirection: "row", justifyContent: "space-around"}}>
                            <FormLabel style={{marginTop: "15px", fontSize: "18px"}}>
                                Phone Number
                            </FormLabel>
                            <TextField {...register("phoneNumber")}>
                                id="phoneNumber"
                                label="Phone Number"
                                variant="outlined"
                            </TextField>
                        </Container>

                        <Button type="submit" variant="contained" sx={{ backgroundColor: colors.blue[500] }}>Add author</Button>
                    </form>
                </CardContent>
            </Card>
        </Container>
    );
}