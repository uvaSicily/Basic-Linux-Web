
const store = new store({
    state(){
        return{
            IsShowLogin:false,
            IsShowRegister:false,
            name:localStorage["name"],
            type:localStorage["type"]
        }
    },
    mutations:{
        OpenLogin(state) {
            state.IsShowLogin = true;
        },
        CloseLogin(state) {
            state.IsShowLogin = false;
        },
        OpenRegister(state) {
            state.IsShowRegister = false;
        },
        closeRegister(state) {
            state.IsShowRegister = false;
        },
        Settingname(state, name) {
            state.name = name;
        }
    }
})
export default store;