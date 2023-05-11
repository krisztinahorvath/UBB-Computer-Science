import { Component, OnInit } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Router } from '@angular/router';

@Component({
  selector: 'app-document-home',
  templateUrl: './document-home.component.html',
  styleUrls: ['./document-home.component.css']
})
export class DocumentHomeComponent implements OnInit {
  documents: any[] = [];

  constructor(private http: HttpClient, private router: Router) { }

  onAddClick(): void{
    this.router.navigate(['/add']);
  }

  onDeleteClick(documentId: string): void {
    this.router.navigate(['/delete', documentId]);
  }

  onBrowserClick(): void {
    this.router.navigate(['/browse']);
  }


  ngOnInit() {
    this.http.get<any[]>('http://localhost/lab7/php/getAll.php').subscribe(data => {
      this.documents = data;
    });
  }

}