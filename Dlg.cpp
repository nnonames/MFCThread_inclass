void CRFIDDlg::OnReadContinue()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//SetTimer();
	AfxBeginThread(CallThread, (LPVOID)this);
	//LPPOINT currentCursor = new POINT;
	//LPPOINT beforeCursor = new POINT;
	//GetCursorPos(beforeCursor);
	//GetCursorPos(currentCursor);
	//if (beforeCursor->x != currentCursor->x || beforeCursor->y != currentCursor->y) { break; }
}

void CRFIDDlg::StartThread() {
	AfxBeginThread(CallThread, (LPVOID)this);
	//StartThread(LPVOID pParam)
	//return ((CRFIDDlg *)pParam)->CRFIDDlg::OnReadInfinityThread();
}

UINT CRFIDDlg::CallThread(LPVOID p) {
	CRFIDDlg *what = (CRFIDDlg *)p;
	return what->OnReadInfinityThread();
}

UINT CRFIDDlg::OnReadInfinityThread() {
	CString temp, temp1, msg = _T("");

	msg.Format(_T("계속 읽기모드를 시작합니다..."));
	AfxMessageBox(msg, MB_ICONINFORMATION);

	for (int i = 0; ;) {
		//if (){}
		if (i % 5 == 0) {
			if (is_WriteReadCommand(ftHandle, CM1_ISO15693, CM2_ISO15693_ACTIVE + BUZZER_ON,
				writeLength, wirteData, &readLength, readData) == IS_OK)
			{
				printf("ISO 15693 UID : ");
				for (int i = 0; i < readLength; i++)
				{
					temp.Format(_T("%02x "), readData[i]);
					temp1 += temp;
				}
				m_strRfid = temp1;
				temp1 = _T("");
				//UpdateData(FALSE);
				printf("\n");
				isUpdated = true;
				msg.Format(_T("카드가 읽혔습니다... >> : %s"), m_strRfid);
				AfxMessageBox(msg, MB_ICONINFORMATION);
			}
			else if (is_WriteReadCommand(ftHandle, CM1_ISO14443AB, CM2_ISO14443A_ACTIVE + BUZZER_ON,
				writeLength, wirteData, &readLength, readData) == IS_OK)
			{
				printf("ISO 14443AB UID : ");
				for (int i = 0; i < readLength; i++)
				{
					//printf("%02x ", readData[i]);
					temp.Format(_T("%02x "), readData[i]);
					temp1 += temp;
				}
				m_strRfid = temp1;
				temp1 = _T("");
				printf("\n");
				isUpdated = true;
				msg.Format(_T("카드가 읽혔습니다... >> : %s"), m_strRfid);
				AfxMessageBox(msg, MB_ICONINFORMATION);
			}
		}
		if (i >= 1000000) { i = 0; }
		i++;
	}
	return 0;
}