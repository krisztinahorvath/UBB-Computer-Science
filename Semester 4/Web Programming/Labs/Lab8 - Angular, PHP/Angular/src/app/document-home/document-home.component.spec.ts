import { ComponentFixture, TestBed } from '@angular/core/testing';

import { DocumentHomeComponent } from './document-home.component';

describe('DocumentHomeComponent', () => {
  let component: DocumentHomeComponent;
  let fixture: ComponentFixture<DocumentHomeComponent>;

  beforeEach(() => {
    TestBed.configureTestingModule({
      declarations: [DocumentHomeComponent]
    });
    fixture = TestBed.createComponent(DocumentHomeComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});



