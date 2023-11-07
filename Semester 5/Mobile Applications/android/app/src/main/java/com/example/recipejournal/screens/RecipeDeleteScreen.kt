package com.example.recipejournal.screens

import androidx.compose.material3.AlertDialog
import androidx.compose.material3.Button
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable

@Composable
fun RecipeDeletePopUp(
    onDeleteConfirmed: () -> Unit,
    onCancel: () -> Unit
) {
    AlertDialog(
        onDismissRequest = onCancel,
        title = { Text("Delete Recipe") },
        text = { Text("Are you sure you want to delete this recipe?") },
        confirmButton = {
            Button(
                onClick = onDeleteConfirmed
            ) {
                Text("Delete")
            }
        },
        dismissButton = {
            Button(
                onClick = onCancel
            ) {
                Text("Cancel")
            }
        }
    )
}