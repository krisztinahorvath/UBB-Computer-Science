package com.example.recipejournal.screens

import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.ArrowBack
import androidx.compose.material3.Button
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.Icon
import androidx.compose.material3.IconButton
import androidx.compose.material3.Snackbar
import androidx.compose.material3.Text
import androidx.compose.material3.TextField
import androidx.compose.material3.TopAppBar
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Modifier
import androidx.compose.ui.unit.dp
import androidx.navigation.NavHostController
import com.example.recipejournal.viewmodels.RecipeViewModel
import com.example.recipejournal.models.Recipe


@Composable
fun CustomSnackbar(
    errorMessage: String?,
    onDismiss: () -> Unit
) {
    errorMessage?.let {
        Snackbar(
            modifier = Modifier.padding(16.dp),
            action = {
                Button(
                    onClick = { onDismiss() },
                ) {
                    Text("Dismiss")
                }
            }
        ) {
            Text(it)
        }
    }
}

@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun RecipeCreate(
    viewModel: RecipeViewModel,
    onRecipeCreated: () -> Unit,
    navController: NavHostController
) {
    var name by remember { mutableStateOf("") }
    var ingredients by remember { mutableStateOf("") }
    var directions by remember { mutableStateOf("") }
    var time by remember { mutableStateOf("") }
    var servings by remember { mutableStateOf("") }

    var showError by remember { mutableStateOf(false) }
    var errorMessage by remember { mutableStateOf<String?>(null) }


    Column(
        modifier = Modifier
            .fillMaxSize()
            .padding(16.dp)
    ) {
        TopAppBar(
            title = { Text("My Recipes") },
            navigationIcon = {
                IconButton(
                    onClick = {
                            navController.navigate(RecipeNavigation.RECIPE_LIST)
                    }
                ) {
                    Icon(imageVector = Icons.Default.ArrowBack, contentDescription = "Back", modifier = Modifier.size(35.dp))
                }
            }
        )

        TextField(
            value = name,
            onValueChange = { name = it },
            label = { Text("Name") }
        )

        TextField(
            value = ingredients,
            onValueChange = { ingredients = it },
            label = { Text("Ingredients (comma separated)") }
        )


        TextField(
            value = directions,
            onValueChange = { directions = it },
            label = { Text("Directions") }
        )

        TextField(
            value = time,
            onValueChange = { time = it },
            label = { Text("Preparation time (in minutes)") }
        )

        TextField(
            value = servings,
            onValueChange = { servings = it },
            label = { Text("Number of servings") }
        )


        Button(
            onClick = {

                if (name.isEmpty() || ingredients.isEmpty()) {
                    showError = true
                    errorMessage = "Name and Ingredients are required fields."
                } else {
                    try {
                        var servingsInt: Int = 0;
                        var timeInt: Int = 0;

                        if(!servings.isEmpty())
                            servingsInt = servings.toInt()
                        if(!time.isEmpty())
                            timeInt = time.toInt()

                        if(servingsInt < 0 || timeInt < 0)
                            throw NumberFormatException()

                        val newRecipe = Recipe(
                            id = 1, // just for show, an actual id is assigned in the model view
                            name = name,
                            directions = directions,
                            ingredients = ingredients,
                            servings = servingsInt,
                            time = timeInt
                        )
                        viewModel.addRecipe(newRecipe)
                        onRecipeCreated()
                    } catch (e: NumberFormatException) {
                        showError = true
                        errorMessage = "Only introduce valid positive numbers for servings and time."
                    }
                }
            }
        ) {
            Text("Create Recipe")
        }

        CustomSnackbar(errorMessage) {
            showError = false
            errorMessage = null
        }
    }
}