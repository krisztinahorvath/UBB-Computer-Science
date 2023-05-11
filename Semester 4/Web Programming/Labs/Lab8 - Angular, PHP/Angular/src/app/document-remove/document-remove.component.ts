import { Component, OnInit } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { ActivatedRoute, Router } from '@angular/router';

@Component({
  selector: 'app-document-remove',
  templateUrl: './document-remove.component.html',
  styleUrls: ['./document-remove.component.css']
})
export class DocumentRemoveComponent implements OnInit {
    documentId: string | undefined;

    constructor(private http: HttpClient, private route: ActivatedRoute, private router: Router) {
      this.route.queryParams.subscribe(params => {
        this.documentId = params['id'];
        console.log(this.documentId);
      });
    }
  
    ngOnInit(): void {
    }
  

    onDeleteConfirmed(): void {
      this.http.delete(`http://localhost/lab7/php/delete.php?id=${this.documentId}`).subscribe(() => {
        
      });
      this.router.navigate(['/home']);
    }
  
    onCancel(): void {
      this.router.navigate(['/home']);
    }
}
