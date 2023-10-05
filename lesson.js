const urlParams = new URLSearchParams(window.location.search);
const lessonNameParam = urlParams.get('lessonName');
if (lessonNameParam) {
    fetch('http://localhost:5243/api/les/GetLessons', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ lessonName: lessonNameParam })
    })
    .then(res => res.json())
    .then(data => {
        // 从返回的数据中获取课程对象
        const lesson = data.result[0];
    
        // 获取 HTML 元素
        const lessonImage = document.getElementById('lessonImage');
        const lessonNameElem = document.getElementById('lessonName');
        const lessonText = document.getElementById('lessonText');
        const lessonTip = document.getElementById('lessonTip');
        const lessonTeacher = document.getElementById('lessonTeacher');
        const lessonButton = document.querySelector('.btn');
        const lessonId = document.getElementById('lessonId');
    
        // 将课程信息替换到对应的 HTML 元素中
        lessonImage.src = lesson.lessonImage;
        lessonNameElem.textContent = lesson.lessonName;
        lessonText.textContent = lesson.lessonText;
        lessonTeacher.textContent = lesson.lessonTeacher;
        lessonTip.textContent = lesson.lessonTip;
        lessonButton.href = lesson.lessonUrl || '/bishe/video/video.html';
        lessonId.textContent = lesson.id;
    
        // 保存教师 id 到本地
        localStorage.setItem('lessonTeacher', lesson.lessonTeacher);
        localStorage.setItem('lessonId', lesson.id);
    })
    .catch(err => console.error(err));
}