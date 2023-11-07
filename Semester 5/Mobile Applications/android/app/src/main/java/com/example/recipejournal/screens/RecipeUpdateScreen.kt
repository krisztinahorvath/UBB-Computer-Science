package com.example.recipejournal.screens

import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.ArrowBack
import androidx.compose.material3.Button
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.Icon
import androidx.compose.material3.IconButton
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
import com.example.recipejournal.models.Recipe
import com.example.recipejournal.viewmodels.RecipeViewModel
import com.example.recipejournal.viewmodels.SelectedRecipeViewModel

@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun RecipeUpdateScreen(
    viewModel: RecipeViewModel,
    selectedRecipeViewModel: SelectedRecipeViewModel,
    navController: NavHostController
) {
    val selectedRecipeId = selectedRecipeViewModel.selectedRecipeId
    val recipe = viewModel.getRecipeById(selectedRecipeId)

    var name by remember { mutableStateOf(recipe.name) }
    var ingredients by remember { mutableStateOf(recipe.ingredients) }
    var directions by remember { mutableStateOf(recipe.directions) }
    var time by remember { mutableStateOf(recipe.time.toString()) }
    var servings by remember { mutableStateOf(recipe.servings.toString()) }

    var showError by remember { mutableStateOf(false) }
    var errorMessage by remember { mutableStateOf<String?>(null) }

    Column(
        modifier = Modifier
            .fillMaxSize()
            .padding(16.dp)
    ) {
        TopAppBar(
            title = { Text("Update Recipe") },
            navigationIcon = {
                IconButton(
                    onClick = {
                        navController.navigateUp()
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

        Column(
            modifier = Modifier.fillMaxWidth()
        ) {
            Button(
                onClick = {
                    if (name.isEmpty() || ingredients.isEmpty()) {
                        showError = true
                        errorMessage = "Name and Ingredients are required fields."
                    } else {
                        try {
                            val servingsInt = servings.toInt()
                            val timeInt = time.toInt()

                            if(servingsInt < 0 || timeInt < 0)
                                throw NumberFormatException()

                            val updatedRecipe = Recipe(
                                id = selectedRecipeId,
                                name = name,
                                directions = directions,
                                ingredients = ingredients,
                                servings = servingsInt,
                                time = timeInt
                            )

                            viewModel.updateRecipe(updatedRecipe)
                            navController.navigateUp()
                        } catch (e: NumberFormatException) {
                            showError = true
                            errorMessage = "Only introduce valid numbers for servings and time."
                        }
                    }
                },
                modifier = Modifier.fillMaxWidth()
            ) {
                Text("Update Recipe")
            }
        }

        CustomSnackbar(errorMessage) {
            showError = false
            errorMessage = null
        }
    }
}

